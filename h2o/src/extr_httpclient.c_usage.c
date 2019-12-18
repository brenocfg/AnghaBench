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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *progname)
{
    fprintf(stderr,
            "Usage: %s [options] <url>\n"
            "Options:\n"
            "  -2 <ratio>   HTTP/2 ratio (between 0 and 100)\n"
            "  -3           HTTP/3-only mode\n"
            "  -b <size>    size of request body (in bytes; default: 0)\n"
            "  -c <size>    size of body chunk (in bytes; default: 10)\n"
            "  -H <name:value>\n"
            "               adds a request header\n"
            "  -i <delay>   send interval between chunks (in msec; default: 0)\n"
            "  -k           skip peer verification\n"
            "  -m <method>  request method (default: GET)\n"
            "  -o <path>    file to which the response body is written (default: stdout)\n"
            "  -t <times>   number of requests to send the request (default: 1)\n"
            "  -h           prints this help\n"
            "\n",
            progname);
}