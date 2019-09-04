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
struct lev_education {int type; int grad_year; int chair; int faculty; int university; int city; int country; scalar_t__ edu_status; scalar_t__ edu_form; } ;
struct education {int primary; int grad_year; int chair; int faculty; int university; int city; int country; int edu_form; int edu_status; struct education* next; } ;

/* Variables and functions */
 int MAX_EDU_FORM ; 
 int MAX_EDU_STATUS ; 
 int /*<<< orphan*/  memset (struct education*,int,int) ; 
 int /*<<< orphan*/  q_chair ; 
 int /*<<< orphan*/  q_edu_form ; 
 int /*<<< orphan*/  q_edu_status ; 
 int /*<<< orphan*/  q_faculty ; 
 int /*<<< orphan*/  q_graduation ; 
 int /*<<< orphan*/  q_uni_city ; 
 int /*<<< orphan*/  q_uni_country ; 
 int /*<<< orphan*/  q_univ ; 
 int /*<<< orphan*/  user_add_field (int,int /*<<< orphan*/ ,int) ; 
 struct education* zmalloc (int) ; 

__attribute__((used)) static void store_edu (int uid, struct education **to, struct lev_education *D) {
  int prim = D->type & 1;
  int edu_form = (unsigned char) D->edu_form;
  int edu_status = (unsigned char) D->edu_status;
  struct education *E;
  if (prim) {
    for (E = *to; E; E = E->next) {
      E->primary = 0;
    }
  }
  E = zmalloc (sizeof (struct education));
  memset (E, -1, sizeof(*E));
  E->next = *to;
  if (edu_form > MAX_EDU_FORM) { 
    edu_form = 0; 
  }
  if (edu_status > MAX_EDU_STATUS) { 
    edu_status = 0; 
  }
#define CPY(__x,__f) user_add_field (uid, __f, E->__x = D->__x);  
#define CPYL(__x,__f) user_add_field (uid, __f, E->__x = __x);  
  CPY(grad_year, q_graduation);
  CPY(chair, q_chair);
  CPY(faculty, q_faculty);
  CPY(university, q_univ);
  CPY(city, q_uni_city);
  CPY(country, q_uni_country);
  CPYL(edu_form, q_edu_form);
  CPYL(edu_status, q_edu_status);
#undef CPY
#undef CPYL
  E->primary = prim;
  *to = E;
}