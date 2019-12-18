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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  mini_inetd (int,int /*<<< orphan*/ *) ; 
 int proto (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
doit (int port, const char *service)
{
    mini_inetd (port, NULL);

    return proto (STDIN_FILENO, service);
}