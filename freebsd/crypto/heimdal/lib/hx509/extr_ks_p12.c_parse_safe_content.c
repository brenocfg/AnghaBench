#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hx509_collector {int dummy; } ;
typedef  int /*<<< orphan*/  sc ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_9__ {size_t len; TYPE_2__* val; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  bagAttributes; TYPE_1__ bagValue; int /*<<< orphan*/  bagId; } ;
typedef  TYPE_3__ PKCS12_SafeContents ;

/* Variables and functions */
 int decode_PKCS12_SafeContents (unsigned char const*,size_t,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_PKCS12_SafeContents (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_pkcs12_type (int /*<<< orphan*/ ,struct hx509_collector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_safe_content(hx509_context context,
		   struct hx509_collector *c,
		   const unsigned char *p, size_t len)
{
    PKCS12_SafeContents sc;
    int ret;
    size_t i;

    memset(&sc, 0, sizeof(sc));

    ret = decode_PKCS12_SafeContents(p, len, &sc, NULL);
    if (ret)
	return ret;

    for (i = 0; i < sc.len ; i++)
	parse_pkcs12_type(context,
			  c,
			  &sc.val[i].bagId,
			  sc.val[i].bagValue.data,
			  sc.val[i].bagValue.length,
			  sc.val[i].bagAttributes);

    free_PKCS12_SafeContents(&sc);
    return 0;
}