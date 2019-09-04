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
struct lev_address_extended {int* text; void* atype; void* country; void* street; void* station; void* district; void* city; void* user_id; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GA ; 
 int /*<<< orphan*/  GB ; 
 int /*<<< orphan*/  Gc ; 
 int /*<<< orphan*/  Gd ; 
 void** I ; 
 scalar_t__ LEV_TARG_ADDR_EXT_ADD ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t adr_city_id ; 
 size_t adr_country_id ; 
 size_t adr_district_id ; 
 size_t adr_house_id ; 
 size_t adr_member_id ; 
 size_t adr_place_id ; 
 size_t adr_station_id ; 
 size_t adr_street_id ; 
 size_t adr_type ; 
 int /*<<< orphan*/  fits (void*) ; 
 char* lookup_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 void* user_id ; 
 struct lev_address_extended* write_alloc (int) ; 

void process_addresses_row (void) {
  struct lev_address_extended *A;
  char *house, *name;
  int house_len, name_len;
  int len;

  user_id = I[adr_member_id];

  if (!fits(user_id)) {
    return;
  }

  house = lookup_name (GA, Gc, I[adr_house_id], &house_len, 64);
  name = lookup_name (GB, Gd, I[adr_place_id], &name_len, 128);

  len = house_len + 1 + name_len;

  A = write_alloc (len + 27);
  A->type = LEV_TARG_ADDR_EXT_ADD + len;
  A->user_id = user_id;
  A->city = I[adr_city_id];
  A->district = I[adr_district_id];
  A->station = I[adr_station_id];
  A->street = I[adr_street_id];
  A->country = I[adr_country_id];
  A->atype = I[adr_type];

  if (house_len) {
    memcpy (A->text, house, house_len);
  }
  A->text[house_len] = 9;
  if (name_len) {
    memcpy (A->text + house_len + 1, name, name_len);
  }
  A->text[len] = 0;

  adj_rec++;

}