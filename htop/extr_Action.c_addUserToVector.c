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
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  Object ;

/* Variables and functions */
 scalar_t__ ListItem_new (char*,int) ; 
 int /*<<< orphan*/  Panel_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void addUserToVector(int key, void* userCast, void* panelCast) {
   char* user = (char*) userCast;
   Panel* panel = (Panel*) panelCast;
   Panel_add(panel, (Object*) ListItem_new(user, key));
}