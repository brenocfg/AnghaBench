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
struct client {int dummy; } ;

/* Variables and functions */
 int GSMERR_OK ; 
 int /*<<< orphan*/  eGetTargetName ; 
 int /*<<< orphan*/  put32 (struct client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retstring (struct client*,char*) ; 

__attribute__((used)) static int
get_targetname(struct client *client,
	       char **target)
{
    put32(client, eGetTargetName);
    retstring(client, *target);
    return GSMERR_OK;
}