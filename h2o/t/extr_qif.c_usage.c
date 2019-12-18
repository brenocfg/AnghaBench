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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void usage(const char *cmd)
{
    printf("Usage: %s [options] [input-file [output-file]]\n"
           "Options:\n"
           "  -a         simulate ACK (encoder only)\n"
           "  -b [max]   maximum number of blocked streams\n"
           "  -d         decode (default is encode)\n"
           "  -r         handling series of responses (default is requests)\n"
           "  -s [bits]  header table size bits (default is 12; i.e. 4096 bytes)\n"
           "\n",
           cmd);
    exit(0);
}