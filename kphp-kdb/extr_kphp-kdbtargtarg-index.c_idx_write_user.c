#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int user_id; int rate; int last_visited; int uni_city; int region; int /*<<< orphan*/  clicked_ads; int /*<<< orphan*/  inactive_ads; int /*<<< orphan*/  active_ads; TYPE_2__* langs; TYPE_1__* grp; struct school* mil; struct school* inter; struct school* addr; struct school* work; struct school* sch; struct school* edu; int /*<<< orphan*/  proposal; int /*<<< orphan*/  hometown; int /*<<< orphan*/  religion; int /*<<< orphan*/  name; int /*<<< orphan*/  proposal_hashes; int /*<<< orphan*/  hometown_hashes; int /*<<< orphan*/  religion_hashes; int /*<<< orphan*/  inter_hashes; int /*<<< orphan*/  name_hashes; int /*<<< orphan*/  custom_fields; int /*<<< orphan*/  gcountry; int /*<<< orphan*/  hidden; int /*<<< orphan*/  cvisited; int /*<<< orphan*/  iiothers; int /*<<< orphan*/  ppriority; int /*<<< orphan*/  alcohol; int /*<<< orphan*/  smoking; int /*<<< orphan*/  height; int /*<<< orphan*/  timezone; int /*<<< orphan*/  operator; int /*<<< orphan*/  browser; int /*<<< orphan*/  has_photo; int /*<<< orphan*/  privacy; int /*<<< orphan*/  cute; int /*<<< orphan*/  uni_country; int /*<<< orphan*/  mstatus; int /*<<< orphan*/  sex; int /*<<< orphan*/  political; int /*<<< orphan*/  bday_year; int /*<<< orphan*/  bday_month; int /*<<< orphan*/  bday_day; int /*<<< orphan*/  user_group_types; } ;
typedef  TYPE_3__ user_t ;
struct school {int grad_year; int chair; int faculty; int university; int city; int school; int company; int district; int station; int street; int unit_id; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; struct school* next; int /*<<< orphan*/  text; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  house; int /*<<< orphan*/  name_hashes; int /*<<< orphan*/  house_hashes; int /*<<< orphan*/  atype; int /*<<< orphan*/  country; int /*<<< orphan*/  job; int /*<<< orphan*/  company_name; int /*<<< orphan*/  job_hashes; int /*<<< orphan*/  spec; int /*<<< orphan*/  spec_hashes; int /*<<< orphan*/  sch_type; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  grad; int /*<<< orphan*/  primary; int /*<<< orphan*/  edu_status; int /*<<< orphan*/  edu_form; } ;
struct military {int grad_year; int chair; int faculty; int university; int city; int school; int company; int district; int station; int street; int unit_id; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; struct military* next; int /*<<< orphan*/  text; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  house; int /*<<< orphan*/  name_hashes; int /*<<< orphan*/  house_hashes; int /*<<< orphan*/  atype; int /*<<< orphan*/  country; int /*<<< orphan*/  job; int /*<<< orphan*/  company_name; int /*<<< orphan*/  job_hashes; int /*<<< orphan*/  spec; int /*<<< orphan*/  spec_hashes; int /*<<< orphan*/  sch_type; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  grad; int /*<<< orphan*/  primary; int /*<<< orphan*/  edu_status; int /*<<< orphan*/  edu_form; } ;
struct interest {int grad_year; int chair; int faculty; int university; int city; int school; int company; int district; int station; int street; int unit_id; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; struct interest* next; int /*<<< orphan*/  text; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  house; int /*<<< orphan*/  name_hashes; int /*<<< orphan*/  house_hashes; int /*<<< orphan*/  atype; int /*<<< orphan*/  country; int /*<<< orphan*/  job; int /*<<< orphan*/  company_name; int /*<<< orphan*/  job_hashes; int /*<<< orphan*/  spec; int /*<<< orphan*/  spec_hashes; int /*<<< orphan*/  sch_type; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  grad; int /*<<< orphan*/  primary; int /*<<< orphan*/  edu_status; int /*<<< orphan*/  edu_form; } ;
struct education {int grad_year; int chair; int faculty; int university; int city; int school; int company; int district; int station; int street; int unit_id; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; struct education* next; int /*<<< orphan*/  text; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  house; int /*<<< orphan*/  name_hashes; int /*<<< orphan*/  house_hashes; int /*<<< orphan*/  atype; int /*<<< orphan*/  country; int /*<<< orphan*/  job; int /*<<< orphan*/  company_name; int /*<<< orphan*/  job_hashes; int /*<<< orphan*/  spec; int /*<<< orphan*/  spec_hashes; int /*<<< orphan*/  sch_type; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  grad; int /*<<< orphan*/  primary; int /*<<< orphan*/  edu_status; int /*<<< orphan*/  edu_form; } ;
struct company {int grad_year; int chair; int faculty; int university; int city; int school; int company; int district; int station; int street; int unit_id; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; struct company* next; int /*<<< orphan*/  text; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  house; int /*<<< orphan*/  name_hashes; int /*<<< orphan*/  house_hashes; int /*<<< orphan*/  atype; int /*<<< orphan*/  country; int /*<<< orphan*/  job; int /*<<< orphan*/  company_name; int /*<<< orphan*/  job_hashes; int /*<<< orphan*/  spec; int /*<<< orphan*/  spec_hashes; int /*<<< orphan*/  sch_type; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  grad; int /*<<< orphan*/  primary; int /*<<< orphan*/  edu_status; int /*<<< orphan*/  edu_form; } ;
struct address {int grad_year; int chair; int faculty; int university; int city; int school; int company; int district; int station; int street; int unit_id; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; struct address* next; int /*<<< orphan*/  text; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  house; int /*<<< orphan*/  name_hashes; int /*<<< orphan*/  house_hashes; int /*<<< orphan*/  atype; int /*<<< orphan*/  country; int /*<<< orphan*/  job; int /*<<< orphan*/  company_name; int /*<<< orphan*/  job_hashes; int /*<<< orphan*/  spec; int /*<<< orphan*/  spec_hashes; int /*<<< orphan*/  sch_type; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  grad; int /*<<< orphan*/  primary; int /*<<< orphan*/  edu_status; int /*<<< orphan*/  edu_form; } ;
struct TYPE_7__ {int cur_langs; int /*<<< orphan*/  L; } ;
struct TYPE_6__ {int cur_groups; int /*<<< orphan*/  G; } ;

/* Variables and functions */
 int /*<<< orphan*/  AdSpace ; 
 int TARG_INDEX_USER_STRUCT_V1_MAGIC ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int get_list_len (struct school*) ; 
 int intree_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_not_ancient ; 
 int /*<<< orphan*/  return_one ; 
 int /*<<< orphan*/  writeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writeout_align (int) ; 
 int /*<<< orphan*/  writeout_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeout_hashlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeout_int (int) ; 
 int /*<<< orphan*/  writeout_short (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeout_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeout_ushort_check (int) ; 
 int /*<<< orphan*/  writeout_xz ; 
 int /*<<< orphan*/  writeout_xz_not_ancient ; 

__attribute__((used)) static void idx_write_user (user_t *U) {
  assert (U);

  writeout_int (TARG_INDEX_USER_STRUCT_V1_MAGIC);
  writeout_int (U->user_id);
  writeout_int (intree_traverse (AdSpace, U->active_ads, return_one));
  writeout_int (intree_traverse (AdSpace, U->inactive_ads, return_not_ancient));
  writeout_int (intree_traverse (AdSpace, U->clicked_ads, return_one));
  writeout_int (U->rate >> 8);
  writeout_int (U->last_visited);
  writeout_int (U->uni_city);
  writeout_int (U->region);
  writeout (U->user_group_types, 16);
  writeout_char (U->bday_day);
  writeout_char (U->bday_month);
  writeout_short (U->bday_year);
  writeout_char (U->political);
  writeout_char (U->sex);
  writeout_char (U->mstatus);
  writeout_char (U->uni_country);
  writeout_char (U->cute);
  writeout_char (U->privacy);
  writeout_char (U->has_photo);
  writeout_char (U->browser);
  writeout_short (U->operator);
  writeout_short (U->timezone);
  writeout_char (U->height);
  writeout_char (U->smoking);
  writeout_char (U->alcohol);
  writeout_char (U->ppriority);
  writeout_char (U->iiothers);
  writeout_char (U->cvisited);
  writeout_char (U->hidden);
  writeout_char (U->gcountry);
  writeout (U->custom_fields, 15);

  writeout_ushort_check (get_list_len (U->edu));
  writeout_ushort_check (get_list_len (U->sch));
  writeout_ushort_check (get_list_len (U->work));
  writeout_ushort_check (get_list_len (U->addr));
  writeout_ushort_check (get_list_len (U->inter));
  writeout_ushort_check (get_list_len (U->mil));
  writeout_ushort_check (U->grp ? U->grp->cur_groups : 0);
  writeout_ushort_check (U->langs ? U->langs->cur_langs : 0);

  writeout_hashlist (U->name_hashes);
  writeout_hashlist (U->inter_hashes);
  writeout_hashlist (U->religion_hashes);
  writeout_hashlist (U->hometown_hashes);
  writeout_hashlist (U->proposal_hashes);

  writeout_string (U->name);
  writeout_string (U->religion);
  writeout_string (U->hometown);
  writeout_string (U->proposal);

  struct education *E;
  for (E = U->edu; E; E = E->next) {
    writeout_int (E->grad_year);
    writeout_int (E->chair);
    writeout_int (E->faculty);
    writeout_int (E->university);
    writeout_int (E->city);
    writeout_char (E->country);
    writeout_char (E->edu_form);
    writeout_char (E->edu_status);
    writeout_char (E->primary);
  }

  struct school *S;
  for (S = U->sch; S; S = S->next) {
    writeout_int (S->city);
    writeout_int (S->school);
    writeout_short (S->start);
    writeout_short (S->finish);
    writeout_short (S->grad);
    writeout_char (S->country);
    writeout_char (S->sch_class);
    writeout_char (S->sch_type);
    writeout_hashlist (S->spec_hashes);
    writeout_string (S->spec);
  }

  struct company *C;
  for (C = U->work; C; C = C->next) {
    writeout_int (C->city);
    writeout_int (C->company);
    writeout_short (C->start);
    writeout_short (C->finish);
    writeout_char (C->country);
    writeout_hashlist (C->name_hashes);
    writeout_hashlist (C->job_hashes);
    writeout_string (C->company_name);
    writeout_string (C->job);
  }

  struct address *A;
  for (A = U->addr; A; A = A->next) {
    writeout_int (A->city);
    writeout_int (A->district);
    writeout_int (A->station);
    writeout_int (A->street);
    writeout_char (A->country);
    writeout_char (A->atype);
    writeout_hashlist (A->house_hashes);
    writeout_hashlist (A->name_hashes);
    writeout_string (A->house);
    writeout_string (A->name);
  }

  struct interest *I;
  for (I = U->inter; I; I = I->next) {
    writeout_char (I->type);
    writeout_char (I->flags);
    writeout_string (I->text);
  }

  writeout_align (4);
  
  struct military *M;
  for (M = U->mil; M; M = M->next) {
    writeout_int (M->unit_id);
    writeout_short (M->start);
    writeout_short (M->finish);
  }

  if (U->grp) {
    writeout (U->grp->G, U->grp->cur_groups * 4);
  }

  if (U->langs) {
    writeout (U->langs->L, U->langs->cur_langs * 2);
  }

  writeout_align (4);

  intree_traverse (AdSpace, U->active_ads, writeout_xz);
  intree_traverse (AdSpace, U->inactive_ads, writeout_xz_not_ancient);
  intree_traverse (AdSpace, U->clicked_ads, writeout_xz);
}