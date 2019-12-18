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
typedef  int /*<<< orphan*/  h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int server_flag_received ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void server_on_read_second(h2o_socket_t *sock, const char *err)
{
    if (err != NULL) {
        fprintf(stderr, "connection closed unexpectedly:%s\n", err);
        exit(1);
        return;
    }

    fprintf(stderr, "received the flag\n");
    server_flag_received = 1;
}