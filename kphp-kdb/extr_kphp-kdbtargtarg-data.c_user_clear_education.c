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
struct TYPE_3__ {struct education* edu; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;
struct education {struct education* next; int /*<<< orphan*/  edu_status; int /*<<< orphan*/  edu_form; int /*<<< orphan*/  country; int /*<<< orphan*/  city; int /*<<< orphan*/  university; int /*<<< orphan*/  faculty; int /*<<< orphan*/  chair; int /*<<< orphan*/  grad_year; } ;

/* Variables and functions */
 int /*<<< orphan*/  q_chair ; 
 int /*<<< orphan*/  q_edu_form ; 
 int /*<<< orphan*/  q_edu_status ; 
 int /*<<< orphan*/  q_faculty ; 
 int /*<<< orphan*/  q_graduation ; 
 int /*<<< orphan*/  q_uni_city ; 
 int /*<<< orphan*/  q_uni_country ; 
 int /*<<< orphan*/  q_univ ; 
 int /*<<< orphan*/  user_clear_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct education*,int) ; 

__attribute__((used)) static void user_clear_education (user_t *U) {
  struct education *E, *Nx;
  for (E = U->edu; E; E = Nx) {
#define DEL(__x,__f) user_clear_field (U->uid, __f, E->__x);  
    DEL(grad_year, q_graduation);
    DEL(chair, q_chair);
    DEL(faculty, q_faculty);
    DEL(university, q_univ);
    DEL(city, q_uni_city);
    DEL(country, q_uni_country);
    DEL(edu_form, q_edu_form);
    DEL(edu_status, q_edu_status);
#undef DEL
    Nx = E->next;
    zfree (E, sizeof (struct education));
  }
  U->edu = 0;
}