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
typedef  int pid_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (char*) ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  exec_i3_utility (char*,char**) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pipe (int*) ; 
 int read (int,char*,int) ; 
 char* scalloc (int,int) ; 
 char* srealloc (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wait (int*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int writeall (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *migrate_config(char *input, off_t size) {
    int writepipe[2];
    int readpipe[2];

    if (pipe(writepipe) != 0 ||
        pipe(readpipe) != 0) {
        warn("migrate_config: Could not create pipes");
        return NULL;
    }

    pid_t pid = fork();
    if (pid == -1) {
        warn("Could not fork()");
        return NULL;
    }

    /* child */
    if (pid == 0) {
        /* close writing end of writepipe, connect reading side to stdin */
        close(writepipe[1]);
        dup2(writepipe[0], 0);

        /* close reading end of readpipe, connect writing side to stdout */
        close(readpipe[0]);
        dup2(readpipe[1], 1);

        static char *argv[] = {
            NULL, /* will be replaced by the executable path */
            NULL};
        exec_i3_utility("i3-migrate-config-to-v4", argv);
    }

    /* parent */

    /* close reading end of the writepipe (connected to the script’s stdin) */
    close(writepipe[0]);

    /* write the whole config file to the pipe, the script will read everything
     * immediately */
    if (writeall(writepipe[1], input, size) == -1) {
        warn("Could not write to pipe");
        return NULL;
    }
    close(writepipe[1]);

    /* close writing end of the readpipe (connected to the script’s stdout) */
    close(readpipe[1]);

    /* read the script’s output */
    int conv_size = 65535;
    char *converted = scalloc(conv_size, 1);
    int read_bytes = 0, ret;
    do {
        if (read_bytes == conv_size) {
            conv_size += 65535;
            converted = srealloc(converted, conv_size);
        }
        ret = read(readpipe[0], converted + read_bytes, conv_size - read_bytes);
        if (ret == -1) {
            warn("Cannot read from pipe");
            FREE(converted);
            return NULL;
        }
        read_bytes += ret;
    } while (ret > 0);

    /* get the returncode */
    int status;
    wait(&status);
    if (!WIFEXITED(status)) {
        fprintf(stderr, "Child did not terminate normally, using old config file (will lead to broken behaviour)\n");
        FREE(converted);
        return NULL;
    }

    int returncode = WEXITSTATUS(status);
    if (returncode != 0) {
        fprintf(stderr, "Migration process exit code was != 0\n");
        if (returncode == 2) {
            fprintf(stderr, "could not start the migration script\n");
            /* TODO: script was not found. tell the user to fix their system or create a v4 config */
        } else if (returncode == 1) {
            fprintf(stderr, "This already was a v4 config. Please add the following line to your config file:\n");
            fprintf(stderr, "# i3 config file (v4)\n");
            /* TODO: nag the user with a message to include a hint for i3 in their config file */
        }
        FREE(converted);
        return NULL;
    }

    return converted;
}