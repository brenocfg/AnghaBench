#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {char* name; char* message; } ;
typedef  TYPE_1__ DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static const char*
format_message_error(DBusError *err) {
    static char buf[1024];
    snprintf(buf, sizeof(buf), "[%s] %s", err->name ? err->name : "", err->message);
    return buf;
}