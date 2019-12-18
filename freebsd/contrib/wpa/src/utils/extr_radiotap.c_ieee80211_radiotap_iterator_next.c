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
typedef  int uint32_t ;
struct ieee80211_radiotap_iterator {int _arg_index; int _bitmap_shifter; int* _arg; int* _next_ns_data; int this_arg_index; int* this_arg; int this_arg_size; int _reset_on_ext; int is_radiotap_ns; int /*<<< orphan*/  _next_bitmap; TYPE_2__* current_namespace; scalar_t__ _max_length; scalar_t__ _rtheader; } ;
struct TYPE_4__ {int n_bits; TYPE_1__* align_size; } ;
struct TYPE_3__ {int align; int size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
#define  IEEE80211_RADIOTAP_EXT 130 
#define  IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE 129 
#define  IEEE80211_RADIOTAP_VENDOR_NAMESPACE 128 
 int /*<<< orphan*/  find_ns (struct ieee80211_radiotap_iterator*,int,int) ; 
 int /*<<< orphan*/  find_override (struct ieee80211_radiotap_iterator*,int*,int*) ; 
 int get_unaligned_le16 (int*) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ ) ; 
 TYPE_2__ radiotap_ns ; 

int ieee80211_radiotap_iterator_next(
	struct ieee80211_radiotap_iterator *iterator)
{
	while (1) {
		int hit = 0;
		int pad, align, size, subns;
		uint32_t oui;

		/* if no more EXT bits, that's it */
		if ((iterator->_arg_index % 32) == IEEE80211_RADIOTAP_EXT &&
		    !(iterator->_bitmap_shifter & 1))
			return -ENOENT;

		if (!(iterator->_bitmap_shifter & 1))
			goto next_entry; /* arg not present */

		/* get alignment/size of data */
		switch (iterator->_arg_index % 32) {
		case IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE:
		case IEEE80211_RADIOTAP_EXT:
			align = 1;
			size = 0;
			break;
		case IEEE80211_RADIOTAP_VENDOR_NAMESPACE:
			align = 2;
			size = 6;
			break;
		default:
#ifdef RADIOTAP_SUPPORT_OVERRIDES
			if (find_override(iterator, &align, &size)) {
				/* all set */
			} else
#endif
			if (!iterator->current_namespace ||
			    iterator->_arg_index >= iterator->current_namespace->n_bits) {
				if (iterator->current_namespace == &radiotap_ns)
					return -ENOENT;
				align = 0;
			} else {
				align = iterator->current_namespace->align_size[iterator->_arg_index].align;
				size = iterator->current_namespace->align_size[iterator->_arg_index].size;
			}
			if (!align) {
				/* skip all subsequent data */
				iterator->_arg = iterator->_next_ns_data;
				/* give up on this namespace */
				iterator->current_namespace = NULL;
				goto next_entry;
			}
			break;
		}

		/*
		 * arg is present, account for alignment padding
		 *
		 * Note that these alignments are relative to the start
		 * of the radiotap header.  There is no guarantee
		 * that the radiotap header itself is aligned on any
		 * kind of boundary.
		 *
		 * The above is why get_unaligned() is used to dereference
		 * multibyte elements from the radiotap area.
		 */

		pad = ((unsigned long)iterator->_arg -
		       (unsigned long)iterator->_rtheader) & (align - 1);

		if (pad)
			iterator->_arg += align - pad;

		if (iterator->_arg_index % 32 == IEEE80211_RADIOTAP_VENDOR_NAMESPACE) {
			int vnslen;

			if ((unsigned long)iterator->_arg + size -
			    (unsigned long)iterator->_rtheader >
			    (unsigned long)iterator->_max_length)
				return -EINVAL;

			oui = (*iterator->_arg << 16) |
				(*(iterator->_arg + 1) << 8) |
				*(iterator->_arg + 2);
			subns = *(iterator->_arg + 3);

			find_ns(iterator, oui, subns);

			vnslen = get_unaligned_le16(iterator->_arg + 4);
			iterator->_next_ns_data = iterator->_arg + size + vnslen;
			if (!iterator->current_namespace)
				size += vnslen;
		}

		/*
		 * this is what we will return to user, but we need to
		 * move on first so next call has something fresh to test
		 */
		iterator->this_arg_index = iterator->_arg_index;
		iterator->this_arg = iterator->_arg;
		iterator->this_arg_size = size;

		/* internally move on the size of this arg */
		iterator->_arg += size;

		/*
		 * check for insanity where we are given a bitmap that
		 * claims to have more arg content than the length of the
		 * radiotap section.  We will normally end up equalling this
		 * max_length on the last arg, never exceeding it.
		 */

		if ((unsigned long)iterator->_arg -
		    (unsigned long)iterator->_rtheader >
		    (unsigned long)iterator->_max_length)
			return -EINVAL;

		/* these special ones are valid in each bitmap word */
		switch (iterator->_arg_index % 32) {
		case IEEE80211_RADIOTAP_VENDOR_NAMESPACE:
			iterator->_reset_on_ext = 1;

			iterator->is_radiotap_ns = 0;
			/*
			 * If parser didn't register this vendor
			 * namespace with us, allow it to show it
			 * as 'raw. Do do that, set argument index
			 * to vendor namespace.
			 */
			iterator->this_arg_index =
				IEEE80211_RADIOTAP_VENDOR_NAMESPACE;
			if (!iterator->current_namespace)
				hit = 1;
			goto next_entry;
		case IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE:
			iterator->_reset_on_ext = 1;
			iterator->current_namespace = &radiotap_ns;
			iterator->is_radiotap_ns = 1;
			goto next_entry;
		case IEEE80211_RADIOTAP_EXT:
			/*
			 * bit 31 was set, there is more
			 * -- move to next u32 bitmap
			 */
			iterator->_bitmap_shifter =
				get_unaligned_le32(iterator->_next_bitmap);
			iterator->_next_bitmap++;
			if (iterator->_reset_on_ext)
				iterator->_arg_index = 0;
			else
				iterator->_arg_index++;
			iterator->_reset_on_ext = 0;
			break;
		default:
			/* we've got a hit! */
			hit = 1;
 next_entry:
			iterator->_bitmap_shifter >>= 1;
			iterator->_arg_index++;
		}

		/* if we found a valid arg earlier, return it now */
		if (hit)
			return 0;
	}
}