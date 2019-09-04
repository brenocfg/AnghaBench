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
typedef  int /*<<< orphan*/  template ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int ENOENT ; 
 char* calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int createTmpfileCloexec (char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int posix_fallocate (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
createAnonymousFile(off_t size)
{
    int ret, fd = -1, shm_anon = 0;
#ifdef HAS_MEMFD_CREATE
    fd = memfd_create("glfw-shared", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    if (fd < 0) return -1;
    // We can add this seal before calling posix_fallocate(), as the file
    // is currently zero-sized anyway.
    //
    // There is also no need to check for the return value, we couldn’t do
    // anything with it anyway.
    fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
#elif defined(SHM_ANON)
    fd = shm_open(SHM_ANON, O_RDWR | O_CLOEXEC, 0600);
    if (fd < 0) return -1;
    shm_anon = 1;
#else
    static const char template[] = "/glfw-shared-XXXXXX";
    const char* path;
    char* name;

    path = getenv("XDG_RUNTIME_DIR");
    if (!path)
    {
        errno = ENOENT;
        return -1;
    }

    name = calloc(strlen(path) + sizeof(template), 1);
    strcpy(name, path);
    strcat(name, template);

    fd = createTmpfileCloexec(name);

    free(name);

    if (fd < 0)
        return -1;
#endif
    // posix_fallocate does not work on SHM descriptors
    ret = shm_anon ? ftruncate(fd, size) : posix_fallocate(fd, 0, size);
    if (ret != 0)
    {
        close(fd);
        errno = ret;
        return -1;
    }
    return fd;
}