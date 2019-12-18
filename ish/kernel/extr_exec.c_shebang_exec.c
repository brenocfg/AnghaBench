#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fd {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  header ;
struct TYPE_2__ {int (* read ) (struct fd*,char*,int) ;scalar_t__ (* lseek ) (struct fd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fd*) ; 
 int /*<<< orphan*/  O_RDONLY_ ; 
 int PTR_ERR (struct fd*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int _E2BIG ; 
 int _EIO ; 
 int _ENOEXEC ; 
 int /*<<< orphan*/  fd_close (struct fd*) ; 
 int format_exec (struct fd*,char*,char*,char const*) ; 
 struct fd* generic_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strings_size (char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ stub1 (struct fd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct fd*,char*,int) ; 

__attribute__((used)) static int shebang_exec(struct fd *fd, const char *file, const char *argv, const char *envp) {
    // read the first 128 bytes to get the shebang line out of
    if (fd->ops->lseek(fd, 0, SEEK_SET))
        return _EIO;
    char header[128];
    int size = fd->ops->read(fd, header, sizeof(header) - 1);
    if (size < 0)
        return _EIO;
    header[size] = '\0';

    // only look at the first line
    char *newline = strchr(header, '\n');
    if (newline == NULL)
        return _ENOEXEC;
    *newline = '\0';

    // format: #![spaces]interpreter[spaces]argument[spaces]
    char *p = header;
    if (p[0] != '#' || p[1] != '!')
        return _ENOEXEC;
    p += 2;
    while (*p == ' ')
        p++;
    if (*p == '\0')
        return _ENOEXEC;

    char *interpreter = p;
    while (*p != ' ' && *p != '\0')
        p++;
    if (*p != '\0') {
        *p++ = '\0';
        while (*p == ' ')
            p++;
    }

    char *argument = p;
    // strip trailing whitespace
    p = strchr(p, '\0') - 1;
    while (*p == ' ')
        *p-- = '\0';
    if (*argument == '\0')
        argument = NULL;

    const char *argv_rest = argv + strlen(argv) + 1;
    size_t args_size = strings_size(argv_rest);
    size_t extra_args_size = strlen(interpreter) + 1 + strlen(file) + 1;
    if (argument)
        extra_args_size += strlen(argument) + 1;
    if (args_size + extra_args_size >= 4096)
        return _E2BIG;

    char real_argv[4096];
    size_t n = 0;
    strcpy(real_argv, interpreter);
    n += strlen(interpreter) + 1;
    if (argument) {
        strcpy(real_argv + n, argument);
        n += strlen(argument) + 1;
    }
    strcpy(real_argv + n, file);
    n += strlen(file) + 1;
    memcpy(real_argv + n, argv_rest, args_size);

    struct fd *interpreter_fd = generic_open(interpreter, O_RDONLY_, 0);
    if (IS_ERR(interpreter_fd))
        return PTR_ERR(interpreter_fd);
    int err = format_exec(interpreter_fd, interpreter, real_argv, envp);
    fd_close(interpreter_fd);
    return err;
}