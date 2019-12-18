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
struct ifmedia_type_to_subtype {TYPE_1__* options; } ;
struct ifmedia_description {char* ifmt_string; int ifmt_word; } ;
struct TYPE_2__ {struct ifmedia_description* desc; scalar_t__ alias; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct ifmedia_type_to_subtype* get_toptype_ttos (int) ; 
 size_t strlcat (char*,char*,size_t) ; 

void
ifconfig_media_get_options_string(int ifmw, char *buf, size_t buflen)
{
	struct ifmedia_type_to_subtype *ttos;
	struct ifmedia_description *desc;
	int i, seen_option = 0;
	size_t len;

	assert(buflen > 0);
	buf[0] = '\0';
	ttos = get_toptype_ttos(ifmw);
	for (i = 0; ttos->options[i].desc != NULL; i++) {
		if (ttos->options[i].alias) {
			continue;
		}
		for (desc = ttos->options[i].desc;
		    desc->ifmt_string != NULL; desc++) {
			if (ifmw & desc->ifmt_word) {
				if (seen_option++) {
					strlcat(buf, ",", buflen);
				}
				len = strlcat(buf, desc->ifmt_string, buflen);
				assert(len < buflen);
				buf += len;
				buflen -= len;
			}
		}
	}
}