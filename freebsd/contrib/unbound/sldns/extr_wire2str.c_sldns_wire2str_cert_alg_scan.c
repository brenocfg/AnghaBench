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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int name; } ;
typedef  TYPE_1__ sldns_lookup_table ;

/* Variables and functions */
 int /*<<< orphan*/  sldns_cert_algorithms ; 
 TYPE_1__* sldns_lookup_by_id (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sldns_read_uint16 (int /*<<< orphan*/ *) ; 
 int sldns_str_print (char**,size_t*,char*,int) ; 

int sldns_wire2str_cert_alg_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
	sldns_lookup_table *lt;
	int data, w;
	if(*dl < 2) return -1;
	data = (int)sldns_read_uint16(*d);
	lt = sldns_lookup_by_id(sldns_cert_algorithms, data);
	if(lt && lt->name)
		w = sldns_str_print(s, sl, "%s", lt->name);
	else 	w = sldns_str_print(s, sl, "%d", data);
	(*dl)-=2;
	(*d)+=2;
	return w;
}