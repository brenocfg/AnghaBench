#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  enum uni_coding { ____Placeholder_uni_coding } uni_coding ;
struct TYPE_4__ {char const* str; } ;
struct TYPE_3__ {char const* str; } ;

/* Variables and functions */
 int UNI_CODING_ITU ; 
 int UNI_CODING_NET ; 
 TYPE_2__* itu_causes ; 
 TYPE_1__* net_causes ; 

const char *
uni_ie_cause2str(enum uni_coding coding, u_int cause)
{
	if (cause < 128) {
		if (coding == UNI_CODING_ITU)
			return (itu_causes[cause].str);
		if (coding == UNI_CODING_NET) {
			if (net_causes[cause].str != NULL)
				return (net_causes[cause].str);
			return (itu_causes[cause].str);
		}
	}
	return (NULL);
}