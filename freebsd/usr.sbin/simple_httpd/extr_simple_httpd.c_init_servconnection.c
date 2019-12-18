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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  server ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int http_port ; 
 scalar_t__ http_sock ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
init_servconnection(void)
{
	struct sockaddr_in server;

	/* Create a socket */
	http_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (http_sock < 0) {
		perror("socket");
		exit(1);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(http_port);
	server.sin_addr.s_addr = INADDR_ANY;
	if (bind(http_sock, (struct sockaddr *) & server, sizeof(server)) < 0) {
		perror("bind socket");
		exit(1);
	}
        if (verbose) printf("simple_httpd:%d\n",http_port);
}