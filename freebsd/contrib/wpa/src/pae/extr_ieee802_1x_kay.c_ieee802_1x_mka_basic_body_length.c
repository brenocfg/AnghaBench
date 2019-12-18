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
struct TYPE_2__ {scalar_t__ len; } ;
struct ieee802_1x_mka_participant {TYPE_1__ ckn; } ;
struct ieee802_1x_mka_basic_body {int dummy; } ;

/* Variables and functions */
 int MKA_ALIGN_LENGTH (int) ; 

__attribute__((used)) static int
ieee802_1x_mka_basic_body_length(struct ieee802_1x_mka_participant *participant)
{
	int length;

	length = sizeof(struct ieee802_1x_mka_basic_body);
	length += participant->ckn.len;
	return MKA_ALIGN_LENGTH(length);
}