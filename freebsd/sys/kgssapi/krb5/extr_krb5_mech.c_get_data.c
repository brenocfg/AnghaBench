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
typedef  int /*<<< orphan*/  uint8_t ;
struct krb5_data {size_t kd_length; int /*<<< orphan*/  kd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 size_t get_uint32 (int /*<<< orphan*/  const**,size_t*) ; 
 int /*<<< orphan*/  malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_data(const uint8_t **pp, size_t *lenp, struct krb5_data *dp)
{
	size_t sz = get_uint32(pp, lenp);

	dp->kd_length = sz;
	dp->kd_data = malloc(sz, M_GSSAPI, M_WAITOK);

	if (*lenp < sz)
		sz = *lenp;
	bcopy(*pp, dp->kd_data, sz);
	(*pp) += sz;
	(*lenp) -= sz;
}