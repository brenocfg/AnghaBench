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
struct regional {int dummy; } ;
struct nsec3_cached_hash {size_t b32_len; int /*<<< orphan*/  b32; int /*<<< orphan*/  hash_len; int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  log_err (char*,int) ; 
 int /*<<< orphan*/  regional_alloc_init (struct regional*,scalar_t__,size_t) ; 
 int sldns_b32_ntop_extended_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_limit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nsec3_calc_b32(struct regional* region, sldns_buffer* buf, 
	struct nsec3_cached_hash* c)
{
	int r;
	sldns_buffer_clear(buf);
	r = sldns_b32_ntop_extended_hex(c->hash, c->hash_len,
		(char*)sldns_buffer_begin(buf), sldns_buffer_limit(buf));
	if(r < 1) {
		log_err("b32_ntop_extended_hex: error in encoding: %d", r);
		return 0;
	}
	c->b32_len = (size_t)r;
	c->b32 = regional_alloc_init(region, sldns_buffer_begin(buf), 
		c->b32_len);
	if(!c->b32)
		return 0;
	return 1;
}