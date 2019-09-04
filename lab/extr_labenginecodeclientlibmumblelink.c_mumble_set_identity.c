#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_2__ {int /*<<< orphan*/  identity; } ;

/* Variables and functions */
 size_t MIN (int,scalar_t__) ; 
 TYPE_1__* lm ; 
 int /*<<< orphan*/  mbstowcs (int /*<<< orphan*/ ,char const*,size_t) ; 
 scalar_t__ strlen (char const*) ; 

void mumble_set_identity(const char* identity)
{
	size_t len;
	if (!lm)
		return;
	len = MIN(sizeof(lm->identity)/sizeof(wchar_t), strlen(identity)+1);
	mbstowcs(lm->identity, identity, len);
}