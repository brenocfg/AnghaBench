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
 int _asn1_copy (struct asn1_template const*,void const*,void*) ; 
 int /*<<< orphan*/  _asn1_free (struct asn1_template const*,void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
_asn1_copy_top(const struct asn1_template *t, const void *from, void *to)
{
    int ret;
    memset(to, 0, t->offset);
    ret = _asn1_copy(t, from, to);
    if (ret) {
	_asn1_free(t, to);
	memset(to, 0, t->offset);
    }
    return ret;
}