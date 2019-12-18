#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int max_response; unsigned char* response; int /*<<< orphan*/  ctrl_fd; } ;
typedef  TYPE_1__ ftpaux_t ;

/* Variables and functions */
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned char* realloc (unsigned char*,int) ; 
 scalar_t__ socket_wait (int /*<<< orphan*/ ,int) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kftp_get_response(ftpaux_t *aux)
{
	unsigned char c;
	int n = 0;
	char *p;
	if (socket_wait(aux->ctrl_fd, 1) <= 0) return 0;
	while (read(aux->ctrl_fd, &c, 1)) { // FIXME: this is *VERY BAD* for unbuffered I/O
		if (n >= aux->max_response) {
			aux->max_response = aux->max_response? aux->max_response<<1 : 256;
			aux->response = realloc(aux->response, aux->max_response);
		}
		aux->response[n++] = c;
		if (c == '\n') {
			if (n >= 4 && isdigit(aux->response[0]) && isdigit(aux->response[1]) && isdigit(aux->response[2])
				&& aux->response[3] != '-') break;
			n = 0;
			continue;
		}
	}
	if (n < 2) return -1;
	aux->response[n-2] = 0;
	return strtol(aux->response, &p, 0);
}