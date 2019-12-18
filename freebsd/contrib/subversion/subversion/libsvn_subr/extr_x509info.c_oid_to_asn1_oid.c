#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ oid_len; scalar_t__ oid; } ;
typedef  TYPE_1__ asn1_oid ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 TYPE_1__* asn1_oids ; 
 scalar_t__ memcmp (unsigned char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static const asn1_oid *oid_to_asn1_oid(unsigned char *oid, apr_size_t oid_len)
{
  const asn1_oid *entry;

  for (entry = asn1_oids; entry->oid; entry++)
    {
      if (oid_len == entry->oid_len &&
          memcmp(oid, entry->oid, oid_len) == 0)
        return entry;
    }

  return NULL;
}