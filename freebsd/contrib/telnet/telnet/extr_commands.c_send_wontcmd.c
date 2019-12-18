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
 int send_tncmd (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  send_wont ; 

__attribute__((used)) static int
send_wontcmd(char *name)
{
    return(send_tncmd(send_wont, "wont", name));
}