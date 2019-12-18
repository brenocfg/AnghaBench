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
typedef  union uni_ieall {int dummy; } uni_ieall ;
struct unicx {int dummy; } ;
struct uni_connect_ack {int /*<<< orphan*/  unrec; int /*<<< orphan*/  notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int uni_check_ie (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static int
check_connect_ack(struct uni_connect_ack *m, struct unicx *cx)
{
	int ret = 0;

	ret |= uni_check_ie(UNI_IE_NOTIFY, (union uni_ieall *)&m->notify, cx);
	ret |= uni_check_ie(UNI_IE_UNREC, (union uni_ieall *)&m->unrec, cx);

	return ret;
}