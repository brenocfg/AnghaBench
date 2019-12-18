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
struct getargs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arg_printusage (struct getargs*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  exit (int) ; 

__attribute__((used)) static void
client_usage(int code, struct getargs *args, int num_args)
{
    arg_printusage(args, num_args, NULL, "host");
    exit(code);
}