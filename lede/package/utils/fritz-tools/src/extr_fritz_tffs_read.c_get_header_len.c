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
typedef  int /*<<< orphan*/  uint16_t ;
struct tffs_entry_header {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ swap_bytes ; 

__attribute__((used)) static inline uint16_t get_header_len(const struct tffs_entry_header *header)
{
	if (swap_bytes)
		return ntohs(header->len);

	return header->len;
}