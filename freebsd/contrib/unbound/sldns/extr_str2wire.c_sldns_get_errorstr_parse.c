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
struct TYPE_3__ {char const* name; } ;
typedef  TYPE_1__ sldns_lookup_table ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_WIREPARSE_ERROR (int) ; 
 TYPE_1__* sldns_lookup_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wireparse_errors ; 

const char* sldns_get_errorstr_parse(int e)
{
	sldns_lookup_table *lt;
	lt = sldns_lookup_by_id(sldns_wireparse_errors, LDNS_WIREPARSE_ERROR(e));
	return lt?lt->name:"unknown error";
}