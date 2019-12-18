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
typedef  scalar_t__ yajl_status ;
typedef  int /*<<< orphan*/  yajl_handle ;
typedef  char uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  time_t ;
struct stat {int /*<<< orphan*/  st_mtime; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  mtime ;
typedef  int /*<<< orphan*/  destpath ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ I3_IPC_MESSAGE_TYPE_GET_VERSION ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  conn_screen ; 
 double difftime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 char* getpid () ; 
 char* human_readable_version ; 
 int ipc_connect (int /*<<< orphan*/ *) ; 
 int ipc_recv_message (int,scalar_t__*,scalar_t__*,char**) ; 
 int ipc_send_message (int,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 char* loaded_config_file_name ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,char*,int) ; 
 int readlink (char*,char*,size_t) ; 
 char* root_atom_contents (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,char*) ; 
 char* smalloc (size_t) ; 
 char* srealloc (char*,size_t) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  version_callbacks ; 
 int /*<<< orphan*/  yajl_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yajl_free (int /*<<< orphan*/ ) ; 
 scalar_t__ yajl_parse (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 scalar_t__ yajl_status_ok ; 

void display_running_version(void) {
    if (getenv("DISPLAY") == NULL) {
        fprintf(stderr, "\nYour DISPLAY environment variable is not set.\n");
        fprintf(stderr, "Are you running i3 via SSH or on a virtual console?\n");
        fprintf(stderr, "Try DISPLAY=:0 i3 --moreversion\n");
        exit(EXIT_FAILURE);
    }

    char *pid_from_atom = root_atom_contents("I3_PID", conn, conn_screen);
    if (pid_from_atom == NULL) {
        /* If I3_PID is not set, the running version is older than 4.2-200. */
        printf("\nRunning version: < 4.2-200\n");
        exit(EXIT_SUCCESS);
    }

    /* Inform the user of what we are doing. While a single IPC request is
     * really fast normally, in case i3 hangs, this will not terminate. */
    printf("(Getting version from running i3, press ctrl-c to abort…)");
    fflush(stdout);

    int sockfd = ipc_connect(NULL);
    if (ipc_send_message(sockfd, 0, I3_IPC_MESSAGE_TYPE_GET_VERSION,
                         (uint8_t *)"") == -1)
        err(EXIT_FAILURE, "IPC: write()");

    uint32_t reply_length;
    uint32_t reply_type;
    uint8_t *reply;
    int ret;
    if ((ret = ipc_recv_message(sockfd, &reply_type, &reply_length, &reply)) != 0) {
        if (ret == -1)
            err(EXIT_FAILURE, "IPC: read()");
        exit(EXIT_FAILURE);
    }

    if (reply_type != I3_IPC_MESSAGE_TYPE_GET_VERSION)
        errx(EXIT_FAILURE, "Got reply type %d, but expected %d (GET_VERSION)", reply_type, I3_IPC_MESSAGE_TYPE_GET_VERSION);

    yajl_handle handle = yajl_alloc(&version_callbacks, NULL, NULL);

    yajl_status state = yajl_parse(handle, (const unsigned char *)reply, (int)reply_length);
    if (state != yajl_status_ok)
        errx(EXIT_FAILURE, "Could not parse my own reply. That's weird. reply is %.*s", (int)reply_length, reply);

    printf("\rRunning i3 version: %s (pid %s)\n", human_readable_version, pid_from_atom);

    if (loaded_config_file_name) {
        struct stat sb;
        time_t now;
        char mtime[64];
        printf("Loaded i3 config: %s", loaded_config_file_name);
        if (stat(loaded_config_file_name, &sb) == -1) {
            printf("\n");
            ELOG("Cannot stat config file \"%s\"\n", loaded_config_file_name);
        } else {
            strftime(mtime, sizeof(mtime), "%c", localtime(&(sb.st_mtime)));
            time(&now);
            printf(" (Last modified: %s, %.f seconds ago)\n", mtime, difftime(now, sb.st_mtime));
        }
    }

#ifdef __linux__
    size_t destpath_size = 1024;
    ssize_t linksize;
    char *exepath;
    char *destpath = smalloc(destpath_size);

    sasprintf(&exepath, "/proc/%d/exe", getpid());

    while ((linksize = readlink(exepath, destpath, destpath_size)) == (ssize_t)destpath_size) {
        destpath_size = destpath_size * 2;
        destpath = srealloc(destpath, destpath_size);
    }
    if (linksize == -1)
        err(EXIT_FAILURE, "readlink(%s)", exepath);

    /* readlink() does not NULL-terminate strings, so we have to. */
    destpath[linksize] = '\0';

    printf("\n");
    printf("The i3 binary you just called: %s\n", destpath);

    free(exepath);
    sasprintf(&exepath, "/proc/%s/exe", pid_from_atom);

    while ((linksize = readlink(exepath, destpath, destpath_size)) == (ssize_t)destpath_size) {
        destpath_size = destpath_size * 2;
        destpath = srealloc(destpath, destpath_size);
    }
    if (linksize == -1)
        err(EXIT_FAILURE, "readlink(%s)", exepath);

    /* readlink() does not NULL-terminate strings, so we have to. */
    destpath[linksize] = '\0';

    /* Check if "(deleted)" is the readlink result. If so, the running version
     * does not match the file on disk. */
    if (strstr(destpath, "(deleted)") != NULL)
        printf("RUNNING BINARY DIFFERENT FROM BINARY ON DISK!\n");

    /* Since readlink() might put a "(deleted)" somewhere in the buffer and
     * stripping that out seems hackish and ugly, we read the process’s argv[0]
     * instead. */
    free(exepath);
    sasprintf(&exepath, "/proc/%s/cmdline", pid_from_atom);

    int fd;
    if ((fd = open(exepath, O_RDONLY)) == -1)
        err(EXIT_FAILURE, "open(%s)", exepath);
    if (read(fd, destpath, sizeof(destpath)) == -1)
        err(EXIT_FAILURE, "read(%s)", exepath);
    close(fd);

    printf("The i3 binary you are running: %s\n", destpath);

    free(exepath);
    free(destpath);
#endif

    yajl_free(handle);
    free(reply);
    free(pid_from_atom);
}