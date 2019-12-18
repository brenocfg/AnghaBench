#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OSSL_ASYNC_FD ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  ASYNC_WAIT_CTX ;
typedef  int /*<<< orphan*/  ASYNC_JOB ;

/* Variables and functions */
 scalar_t__ ASYNC_WAIT_CTX_get_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ASYNC_WAIT_CTX_set_wait_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/ * ASYNC_get_current_job () ; 
 int /*<<< orphan*/ * ASYNC_get_wait_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASYNC_pause_job () ; 
 scalar_t__ CreatePipe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char DUMMY_CHAR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  engine_dasync_id ; 
 scalar_t__ pipe (int /*<<< orphan*/ *) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wait_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void dummy_pause_job(void) {
    ASYNC_JOB *job;
    ASYNC_WAIT_CTX *waitctx;
    OSSL_ASYNC_FD pipefds[2] = {0, 0};
    OSSL_ASYNC_FD *writefd;
#if defined(ASYNC_WIN)
    DWORD numwritten, numread;
    char buf = DUMMY_CHAR;
#elif defined(ASYNC_POSIX)
    char buf = DUMMY_CHAR;
#endif

    if ((job = ASYNC_get_current_job()) == NULL)
        return;

    waitctx = ASYNC_get_wait_ctx(job);

    if (ASYNC_WAIT_CTX_get_fd(waitctx, engine_dasync_id, &pipefds[0],
                              (void **)&writefd)) {
        pipefds[1] = *writefd;
    } else {
        writefd = OPENSSL_malloc(sizeof(*writefd));
        if (writefd == NULL)
            return;
#if defined(ASYNC_WIN)
        if (CreatePipe(&pipefds[0], &pipefds[1], NULL, 256) == 0) {
            OPENSSL_free(writefd);
            return;
        }
#elif defined(ASYNC_POSIX)
        if (pipe(pipefds) != 0) {
            OPENSSL_free(writefd);
            return;
        }
#endif
        *writefd = pipefds[1];

        if (!ASYNC_WAIT_CTX_set_wait_fd(waitctx, engine_dasync_id, pipefds[0],
                                        writefd, wait_cleanup)) {
            wait_cleanup(waitctx, engine_dasync_id, pipefds[0], writefd);
            return;
        }
    }
    /*
     * In the Dummy async engine we are cheating. We signal that the job
     * is complete by waking it before the call to ASYNC_pause_job(). A real
     * async engine would only wake when the job was actually complete
     */
#if defined(ASYNC_WIN)
    WriteFile(pipefds[1], &buf, 1, &numwritten, NULL);
#elif defined(ASYNC_POSIX)
    if (write(pipefds[1], &buf, 1) < 0)
        return;
#endif

    /* Ignore errors - we carry on anyway */
    ASYNC_pause_job();

    /* Clear the wake signal */
#if defined(ASYNC_WIN)
    ReadFile(pipefds[0], &buf, 1, &numread, NULL);
#elif defined(ASYNC_POSIX)
    if (read(pipefds[0], &buf, 1) < 0)
        return;
#endif
}