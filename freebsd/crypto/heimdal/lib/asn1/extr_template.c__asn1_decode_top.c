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
struct asn1_template {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int _asn1_decode (struct asn1_template const*,unsigned int,unsigned char const*,size_t,void*,size_t*) ; 
 int /*<<< orphan*/  _asn1_free (struct asn1_template const*,void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
_asn1_decode_top(const struct asn1_template *t, unsigned flags, const unsigned char *p, size_t len, void *data, size_t *size)
{
    int ret;
    memset(data, 0, t->offset);
    ret = _asn1_decode(t, flags, p, len, data, size);
    if (ret) {
	_asn1_free(t, data);
	memset(data, 0, t->offset);
    }

    return ret;
}