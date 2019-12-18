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

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *cmd)
{
    fprintf(stderr,
            "Usage: %s [opts] [<host>:]<port>\n"
            "Options: --listen             if set, waits for incoming connection. Otherwise,\n"
            "                              connects to the server running at given address\n"
            "         --reverse-role       if set, reverses the role bet. server and the\n"
            "                              client once the connection is established\n"
            "         --tls                use TLS\n"
            "         --block-size=octets  default write block size\n"
            "         --min-rtt=ms         minimum RTT to enable latency optimization\n"
            "         --max-cwnd=octets    maximum size of CWND to enable latency\n"
            "                              optimization\n",
            cmd);
    exit(1);
}