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
typedef  int /*<<< orphan*/  label ;

/* Variables and functions */
 char* glfwGetJoystickName (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 

__attribute__((used)) static const char* joystick_label(int jid)
{
    static char label[1024];
    snprintf(label, sizeof(label), "%i: %s", jid + 1, glfwGetJoystickName(jid));
    return label;
}