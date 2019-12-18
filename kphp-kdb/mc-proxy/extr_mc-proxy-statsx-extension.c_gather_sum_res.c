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
struct statsx_gather_extra {int /*<<< orphan*/  subcnt; int /*<<< orphan*/  visitors_source; int /*<<< orphan*/  visitors_geoip_countries; int /*<<< orphan*/  visitors_countries; int /*<<< orphan*/  visitors_cities; int /*<<< orphan*/  visitors_sex_age; int /*<<< orphan*/  visitors_section; int /*<<< orphan*/  visitors_polit; int /*<<< orphan*/  visitors_mstatus; int /*<<< orphan*/  visitors_age; int /*<<< orphan*/  visitors_sex; void* valid_until; void* created_at; int /*<<< orphan*/  deletes; int /*<<< orphan*/  unique_visitors; int /*<<< orphan*/  views; } ;
struct gather_entry {int* data; } ;

/* Variables and functions */
 int MAX_AGE ; 
 int /*<<< orphan*/  MAX_CITIES ; 
 int /*<<< orphan*/  MAX_COUNTRIES ; 
 int /*<<< orphan*/  MAX_GEOIP_COUNTRIES ; 
 int MAX_MSTATUS ; 
 int MAX_POLIT ; 
 int MAX_SECTION ; 
 int MAX_SEX ; 
 int MAX_SOURCE ; 
 int MAX_SUBCOUNTER ; 
 void* max (void*,int) ; 
 int* unserialize_list2_raw (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* unserialize_list2_raw_new (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* unserialize_list_raw (int*,int /*<<< orphan*/ ,int) ; 

void gather_sum_res (struct gather_entry *e, struct statsx_gather_extra *C) {
  int *ptr = e->data;
  C->views += *(ptr++);
  C->unique_visitors += *(ptr++);
  C->deletes += *(ptr++);
  C->created_at = max (C->created_at, *ptr);
  ptr++;
  C->valid_until = max (C->valid_until, *ptr);
  ptr++;
  ptr = unserialize_list_raw (ptr, C->visitors_sex, MAX_SEX);
  ptr = unserialize_list_raw (ptr, C->visitors_age, MAX_AGE); 
  ptr = unserialize_list_raw (ptr, C->visitors_mstatus, MAX_MSTATUS); 
  ptr = unserialize_list_raw (ptr, C->visitors_polit, MAX_POLIT); 
  ptr = unserialize_list_raw (ptr, C->visitors_section, MAX_SECTION); 
  ptr = unserialize_list_raw (ptr, C->visitors_sex_age, MAX_AGE * 2); 
  ptr = unserialize_list2_raw_new (ptr, C->visitors_cities, MAX_CITIES);
  ptr = unserialize_list2_raw (ptr, C->visitors_countries, MAX_COUNTRIES);
  ptr = unserialize_list2_raw (ptr, C->visitors_geoip_countries, MAX_GEOIP_COUNTRIES);
  ptr = unserialize_list_raw (ptr, C->visitors_source, MAX_SOURCE);
  ptr = unserialize_list_raw (ptr, C->subcnt, MAX_SUBCOUNTER);
}