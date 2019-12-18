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
typedef  int /*<<< orphan*/ * krb5_context ;

/* Variables and functions */
 int doit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service ; 
 int setup (int /*<<< orphan*/ **,int,char**) ; 

int
main(int argc, char **argv)
{
    krb5_context context = NULL; /* XXX */
    int port = setup(&context, argc, argv);
    return doit (port, service);
}