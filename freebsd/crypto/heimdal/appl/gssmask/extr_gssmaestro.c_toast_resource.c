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
typedef  int int32_t ;

/* Variables and functions */
 int eToastResource ; 
 int /*<<< orphan*/  put32 (struct client*,int) ; 
 int /*<<< orphan*/  ret32 (struct client*,int) ; 

__attribute__((used)) static int
toast_resource(struct client *client,
	       int32_t hCred)
{
    int32_t val;
    put32(client, eToastResource);
    put32(client, hCred);
    ret32(client, val);
    return val;
}