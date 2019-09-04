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
struct object_id {int dummy; } ;
struct min_abbrev_data {unsigned int init_len; scalar_t__* hex; unsigned int cur_len; } ;

/* Variables and functions */
 unsigned int GIT_MAX_RAWSZ ; 
 scalar_t__ get_hex_char_from_oid (struct object_id const*,unsigned int) ; 

__attribute__((used)) static int extend_abbrev_len(const struct object_id *oid, void *cb_data)
{
	struct min_abbrev_data *mad = cb_data;

	unsigned int i = mad->init_len;
	while (mad->hex[i] && mad->hex[i] == get_hex_char_from_oid(oid, i))
		i++;

	if (i < GIT_MAX_RAWSZ && i >= mad->cur_len)
		mad->cur_len = i + 1;

	return 0;
}