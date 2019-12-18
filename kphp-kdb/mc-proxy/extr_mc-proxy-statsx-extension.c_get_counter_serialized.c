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
struct statsx_gather_extra {int views; int unique_visitors; int deletes; int created_at; int valid_until; int* visitors_sex; int /*<<< orphan*/  visitors_source; int /*<<< orphan*/  visitors_geoip_countries; int /*<<< orphan*/  visitors_countries; int /*<<< orphan*/  visitors_cities; int /*<<< orphan*/  visitors_sex_age; int /*<<< orphan*/  visitors_section; int /*<<< orphan*/  visitors_polit; int /*<<< orphan*/  visitors_mstatus; int /*<<< orphan*/  visitors_age; int /*<<< orphan*/  subcnt; } ;

/* Variables and functions */
 int MAX_AGE ; 
 int MAX_CITIES ; 
 int MAX_COUNTRIES ; 
 int MAX_GEOIP_COUNTRIES ; 
 int MAX_MSTATUS ; 
 int MAX_POLIT ; 
 int MAX_SECTION ; 
 int MAX_SEX_AGE ; 
 int MAX_SOURCE ; 
 int MAX_SUBCOUNTER ; 
 scalar_t__ Q_bad_servers ; 
 scalar_t__ Q_raw ; 
 int bad_servers ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int get_counter_serialized_raw (char*,struct statsx_gather_extra*) ; 
 int /*<<< orphan*/  is_null (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_null_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prepare_list2_raw_new (int /*<<< orphan*/ ,int) ; 
 char* serialize_list (char*,char*,int /*<<< orphan*/ ,int) ; 
 char* serialize_list2_new (char*,char*,int /*<<< orphan*/ ,int) ; 
 char* serialize_list2a (char*,char*,int /*<<< orphan*/ ,int) ; 
 char* serialize_subcnt_list (char*,struct statsx_gather_extra*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int get_counter_serialized (char *buffer, struct statsx_gather_extra *C) {
  prepare_list2_raw_new (C->visitors_cities, MAX_CITIES);
  if (Q_raw) {
    return get_counter_serialized_raw (buffer, C);
  }
  int cnt = 6 + (Q_bad_servers != 0);
  char *ptr = buffer;
  if (!is_null (C->visitors_age, MAX_AGE)) { cnt++; }
  if (!is_null (C->visitors_mstatus, MAX_MSTATUS)) { cnt++; }
  if (!is_null (C->visitors_polit, MAX_POLIT)) { cnt++; }
  if (!is_null (C->visitors_section, MAX_SECTION)) { cnt++; }
  if (!is_null_new (C->visitors_cities, 2 * MAX_CITIES)) { cnt++; }
  if (!is_null (C->visitors_sex_age, MAX_SEX_AGE)) { cnt++; }
  if (!is_null (C->visitors_countries, 2 * MAX_COUNTRIES)) { cnt++; }
  if (!is_null (C->visitors_geoip_countries, 2 * MAX_GEOIP_COUNTRIES)) { cnt++; }
  if (!is_null (C->visitors_source, MAX_SOURCE)) { cnt++; }
  if (!is_null (C->subcnt, MAX_SUBCOUNTER)) { cnt++; }
  ptr += sprintf (ptr, "a:%d:{s:5:\"views\";i:%d;s:8:\"visitors\";i:%d;s:7:\"deletes\";i:%d;"
    "s:7:\"created\";i:%d;s:7:\"expires\";i:%d;"
    "s:3:\"sex\";a:2:{i:1;i:%d;i:2;i:%d;}", 
    cnt, C->views, C->unique_visitors, C->deletes, C->created_at, C->valid_until, 
    C->visitors_sex[0], C->visitors_sex[1]);
  if (Q_bad_servers) {
    ptr += sprintf (ptr, "s:11:\"bad_servers\";i:%d;", bad_servers);
  }
  ptr = serialize_list (ptr, "age", C->visitors_age, MAX_AGE); 
  ptr = serialize_list (ptr, "marital_status", C->visitors_mstatus, MAX_MSTATUS); 
  ptr = serialize_list (ptr, "political_views", C->visitors_polit, MAX_POLIT); 
  ptr = serialize_list (ptr, "section", C->visitors_section, MAX_SECTION); 
  ptr = serialize_list (ptr, "sex_age", C->visitors_sex_age, MAX_SEX_AGE); 
  ptr = serialize_list2_new (ptr, "cities", C->visitors_cities, MAX_CITIES);
  ptr = serialize_list2a (ptr, "countries", C->visitors_countries, MAX_COUNTRIES);
  ptr = serialize_list2a (ptr, "geoip_countries", C->visitors_geoip_countries, MAX_GEOIP_COUNTRIES);
  ptr = serialize_list (ptr, "sources", C->visitors_source, MAX_SOURCE);
  ptr = serialize_subcnt_list (ptr, C);
  *ptr++ = '}';
  *ptr = 0;
  if (verbosity >= 4) {
    fprintf (stderr, "%s\n", buffer);
  }
  return ptr - buffer;
}