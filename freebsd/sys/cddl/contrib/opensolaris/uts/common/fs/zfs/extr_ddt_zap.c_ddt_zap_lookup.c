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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uchar_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_3__ {int /*<<< orphan*/  dde_phys; int /*<<< orphan*/  dde_key; } ;
typedef  TYPE_1__ ddt_entry_t ;
typedef  int /*<<< orphan*/  cbuf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DDT_KEY_WORDS ; 
 int /*<<< orphan*/  ddt_decompress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int zap_length_uint64 (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,int*,int*) ; 
 int zap_lookup_uint64 (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ddt_zap_lookup(objset_t *os, uint64_t object, ddt_entry_t *dde)
{
	uchar_t cbuf[sizeof (dde->dde_phys) + 1];
	uint64_t one, csize;
	int error;

	error = zap_length_uint64(os, object, (uint64_t *)&dde->dde_key,
	    DDT_KEY_WORDS, &one, &csize);
	if (error)
		return (error);

	ASSERT(one == 1);
	ASSERT(csize <= sizeof (cbuf));

	error = zap_lookup_uint64(os, object, (uint64_t *)&dde->dde_key,
	    DDT_KEY_WORDS, 1, csize, cbuf);
	if (error)
		return (error);

	ddt_decompress(cbuf, dde->dde_phys, csize, sizeof (dde->dde_phys));

	return (0);
}