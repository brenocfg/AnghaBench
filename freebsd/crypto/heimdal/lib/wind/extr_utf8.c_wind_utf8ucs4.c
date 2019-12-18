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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int WIND_ERR_OVERRUN ; 
 int utf8toutf32 (unsigned char const**,int /*<<< orphan*/ *) ; 

int
wind_utf8ucs4(const char *in, uint32_t *out, size_t *out_len)
{
    const unsigned char *p;
    size_t o = 0;
    int ret;

    for (p = (const unsigned char *)in; *p != '\0'; ++p) {
	uint32_t u;

	ret = utf8toutf32(&p, &u);
	if (ret)
	    return ret;

	if (out) {
	    if (o >= *out_len)
		return WIND_ERR_OVERRUN;
	    out[o] = u;
	}
	o++;
    }
    *out_len = o;
    return 0;
}