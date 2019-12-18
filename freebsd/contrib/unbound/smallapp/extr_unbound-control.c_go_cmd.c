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
typedef  int /*<<< orphan*/  pre ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int UNBOUND_CONTROL_VERSION ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ remote_read (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  remote_write (int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_eof (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send_file (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
go_cmd(SSL* ssl, int fd, int quiet, int argc, char* argv[])
{
	char pre[10];
	const char* space=" ";
	const char* newline="\n";
	int was_error = 0, first_line = 1;
	int i;
	char buf[1024];
	snprintf(pre, sizeof(pre), "UBCT%d ", UNBOUND_CONTROL_VERSION);
	remote_write(ssl, fd, pre, strlen(pre));
	for(i=0; i<argc; i++) {
		remote_write(ssl, fd, space, strlen(space));
		remote_write(ssl, fd, argv[i], strlen(argv[i]));
	}
	remote_write(ssl, fd, newline, strlen(newline));

	if(argc == 1 && strcmp(argv[0], "load_cache") == 0) {
		send_file(ssl, fd, stdin, buf, sizeof(buf));
	}
	else if(argc >= 1 && (strcmp(argv[0], "local_zones") == 0 ||
		strcmp(argv[0], "local_zones_remove") == 0 ||
		strcmp(argv[0], "local_datas") == 0 ||
		strcmp(argv[0], "view_local_datas") == 0 ||
		strcmp(argv[0], "local_datas_remove") == 0)) {
		send_file(ssl, fd, stdin, buf, sizeof(buf));
		send_eof(ssl, fd);
	}

	while(1) {
		if(remote_read(ssl, fd, buf, sizeof(buf)) == 0) {
			break; /* EOF */
		}
		if(first_line && strncmp(buf, "error", 5) == 0) {
			printf("%s", buf);
			was_error = 1;
		} else if (!quiet)
			printf("%s", buf);

		first_line = 0;
	}
	return was_error;
}