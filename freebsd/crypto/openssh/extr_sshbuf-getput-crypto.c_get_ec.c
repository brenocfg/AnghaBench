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
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int EC_POINT_oct2point (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__ const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ const POINT_CONVERSION_UNCOMPRESSED ; 
 size_t SSHBUF_MAX_ECPOINT ; 
 int SSH_ERR_ECPOINT_TOO_LARGE ; 
 int SSH_ERR_INVALID_FORMAT ; 

__attribute__((used)) static int
get_ec(const u_char *d, size_t len, EC_POINT *v, const EC_GROUP *g)
{
	/* Refuse overlong bignums */
	if (len == 0 || len > SSHBUF_MAX_ECPOINT)
		return SSH_ERR_ECPOINT_TOO_LARGE;
	/* Only handle uncompressed points */
	if (*d != POINT_CONVERSION_UNCOMPRESSED)
		return SSH_ERR_INVALID_FORMAT;
	if (v != NULL && EC_POINT_oct2point(g, v, d, len, NULL) != 1)
		return SSH_ERR_INVALID_FORMAT; /* XXX assumption */
	return 0;
}