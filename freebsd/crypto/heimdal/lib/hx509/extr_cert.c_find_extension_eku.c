#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ extnValue; } ;
typedef  TYPE_2__ Extension ;
typedef  int /*<<< orphan*/  ExtKeyUsage ;
typedef  int /*<<< orphan*/  Certificate ;

/* Variables and functions */
 int HX509_EXTENSION_NOT_FOUND ; 
 int /*<<< orphan*/  asn1_oid_id_x509_ce_extKeyUsage ; 
 int decode_ExtKeyUsage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 TYPE_2__* find_extension (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
find_extension_eku(const Certificate *cert, ExtKeyUsage *eku)
{
    const Extension *e;
    size_t size;
    size_t i = 0;

    memset(eku, 0, sizeof(*eku));

    e = find_extension(cert, &asn1_oid_id_x509_ce_extKeyUsage, &i);
    if (e == NULL)
	return HX509_EXTENSION_NOT_FOUND;

    return decode_ExtKeyUsage(e->extnValue.data,
			      e->extnValue.length,
			      eku, &size);
}