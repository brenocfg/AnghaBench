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
typedef  int /*<<< orphan*/  u_char ;
struct isa_config {int dummy; } ;
typedef  scalar_t__ (* pnp_scan_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct isa_config*,int) ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int I16 (int /*<<< orphan*/ *) ; 
 scalar_t__ PNP_RES_TYPE (int /*<<< orphan*/ ) ; 
 int PNP_SRES_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ PNP_SRES_NUM (int /*<<< orphan*/ ) ; 
 scalar_t__ PNP_TAG_END ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct isa_config*,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct isa_config*,int) ; 

u_char
*pnp_scan_resources(device_t dev, u_char *resources, int len,
		    struct isa_config *config, int ldn, pnp_scan_cb *cb)
{
	u_char *p;
	u_char tag;
	int l;

	p = resources;
	while (len > 0) {
		tag = *p++;
		len--;
		if (PNP_RES_TYPE(tag) == 0) {
			/* small resource */
			l = PNP_SRES_LEN(tag);
			if (len < l)
				break;
			if ((*cb)(dev, tag, p, l, config, ldn))
				return (p + l);
			if (PNP_SRES_NUM(tag) == PNP_TAG_END)
				return (p + l);
		} else {
			/* large resource */
			if (len < 2)
				break;
			l = I16(p);
			p += 2;
			len -= 2;
			if (len < l)
				break;
			if ((*cb)(dev, tag, p, l, config, ldn))
				return (p + l);
		}
		p += l;
		len -= l;
	}
	return NULL;
}