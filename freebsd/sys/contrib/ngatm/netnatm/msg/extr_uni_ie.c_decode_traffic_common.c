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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct uni_xtraffic {int ftag; int btag; int fdisc; int bdisc; } ;
struct uni_msg {int* b_rptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_GETF3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRAFFIC_BABR1 ; 
 int /*<<< orphan*/  TRAFFIC_BMBS0 ; 
 int /*<<< orphan*/  TRAFFIC_BMBS1 ; 
 int /*<<< orphan*/  TRAFFIC_BPCR0 ; 
 int /*<<< orphan*/  TRAFFIC_BPCR1 ; 
 int /*<<< orphan*/  TRAFFIC_BSCR0 ; 
 int /*<<< orphan*/  TRAFFIC_BSCR1 ; 
 int /*<<< orphan*/  TRAFFIC_FABR1 ; 
 int /*<<< orphan*/  TRAFFIC_FMBS0 ; 
 int /*<<< orphan*/  TRAFFIC_FPCR0 ; 
 int /*<<< orphan*/  TRAFFIC_FPCR1 ; 
 int /*<<< orphan*/  TRAFFIC_FSCR0 ; 
 int /*<<< orphan*/  TRAFFIC_FSCR1 ; 
 int UNI_TRAFFIC_BDISC ; 
#define  UNI_TRAFFIC_BEST_ID 129 
 scalar_t__ UNI_TRAFFIC_BEST_P ; 
 int UNI_TRAFFIC_BTAG ; 
 int UNI_TRAFFIC_FDISC ; 
 int UNI_TRAFFIC_FTAG ; 
#define  UNI_TRAFFIC_MOPT_ID 128 
 scalar_t__ UNI_TRAFFIC_MOPT_P ; 
 int /*<<< orphan*/  babr1 ; 
 int /*<<< orphan*/  bmbs0 ; 
 int /*<<< orphan*/  bmbs1 ; 
 int /*<<< orphan*/  bpcr0 ; 
 int /*<<< orphan*/  bpcr1 ; 
 int /*<<< orphan*/  bscr0 ; 
 int /*<<< orphan*/  bscr1 ; 
 int /*<<< orphan*/  fabr1 ; 
 int /*<<< orphan*/  fmbs0 ; 
 int /*<<< orphan*/  fpcr0 ; 
 int /*<<< orphan*/  fpcr1 ; 
 int /*<<< orphan*/  fscr0 ; 
 int /*<<< orphan*/  fscr1 ; 

__attribute__((used)) static int
decode_traffic_common(struct uni_xtraffic *ie, struct uni_msg *msg,
    u_int ielen, u_int *present)
{
	u_char c;

	while(ielen--) {
		switch(c = *msg->b_rptr++) {

		  default:
		  rej:
			return -1;

		  DEC_GETF3(TRAFFIC_FPCR0, fpcr0, *present);
		  DEC_GETF3(TRAFFIC_BPCR0, bpcr0, *present);
		  DEC_GETF3(TRAFFIC_FPCR1, fpcr1, *present);
		  DEC_GETF3(TRAFFIC_BPCR1, bpcr1, *present);
		  DEC_GETF3(TRAFFIC_FSCR0, fscr0, *present);
		  DEC_GETF3(TRAFFIC_BSCR0, bscr0, *present);
		  DEC_GETF3(TRAFFIC_FSCR1, fscr1, *present);
		  DEC_GETF3(TRAFFIC_BSCR1, bscr1, *present);
		  DEC_GETF3(TRAFFIC_FMBS0, fmbs0, *present);
		  DEC_GETF3(TRAFFIC_BMBS0, bmbs0, *present);
		  DEC_GETF3(TRAFFIC_BMBS1, bmbs1, *present);
		  DEC_GETF3(TRAFFIC_FABR1, fabr1, *present);
		  DEC_GETF3(TRAFFIC_BABR1, babr1, *present);

		  case UNI_TRAFFIC_BEST_ID:
			*present |= UNI_TRAFFIC_BEST_P;
			break;

		  case UNI_TRAFFIC_MOPT_ID:
			if(ielen == 0)
				return -1;
			ielen--;
			if(!(*present & UNI_TRAFFIC_MOPT_P)) {
				*present |= UNI_TRAFFIC_MOPT_P;
				ie->ftag = (*msg->b_rptr&UNI_TRAFFIC_FTAG)?1:0;
				ie->btag = (*msg->b_rptr&UNI_TRAFFIC_BTAG)?1:0;
				ie->fdisc = (*msg->b_rptr&UNI_TRAFFIC_FDISC)?1:0;
				ie->bdisc = (*msg->b_rptr&UNI_TRAFFIC_BDISC)?1:0;
			} 
			msg->b_rptr++;
			break;
		}
	}
	return 0;
}