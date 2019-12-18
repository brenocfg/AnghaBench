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

/* Variables and functions */
 int /*<<< orphan*/ * I ; 
 int /*<<< orphan*/  PK_events_invite ; 
 int /*<<< orphan*/  PK_friends ; 
 int /*<<< orphan*/  PK_graffiti_send ; 
 int /*<<< orphan*/  PK_groups_invite ; 
 int /*<<< orphan*/  PK_home ; 
 int /*<<< orphan*/  PK_icq ; 
 int /*<<< orphan*/  PK_mail_send ; 
 int /*<<< orphan*/  PK_mobile ; 
 int /*<<< orphan*/  PK_photos_with ; 
 int /*<<< orphan*/  PK_profile ; 
 int /*<<< orphan*/  PK_wall_send ; 
 int /*<<< orphan*/  adj_rec ; 
 int conv_uid (int /*<<< orphan*/ ) ; 
 size_t mp_event_privacy ; 
 size_t mp_friends_privacy ; 
 size_t mp_group_invitations ; 
 size_t mp_h_privacy ; 
 size_t mp_i_privacy ; 
 size_t mp_id ; 
 size_t mp_m_privacy ; 
 size_t mp_notify_mail ; 
 size_t mp_photo_privacy ; 
 size_t mp_pm_privacy ; 
 size_t mp_profile_privacy ; 
 size_t mp_wall_privacy ; 
 int /*<<< orphan*/  output_conv_privacy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  user_id ; 

void process_mempriv_row (void) {
  user_id = I[mp_id];
  int uid = conv_uid (user_id);

  if (uid < 0) {
    return;
  }

  output_conv_privacy (PK_groups_invite,	I[mp_notify_mail],	"*G*A*0*A/A");
  output_conv_privacy (PK_events_invite,	I[mp_event_privacy],	"*G*A*0*A/A");
  output_conv_privacy (PK_mail_send,	I[mp_pm_privacy],	"*G*A*0*A/A");
  output_conv_privacy (PK_wall_send,	I[mp_wall_privacy],	"*G*A*0*A/A");
  output_conv_privacy (PK_graffiti_send,I[mp_group_invitations],"*0*A/A");
  output_conv_privacy (PK_photos_with,	I[mp_photo_privacy],	"*G*A*0*A/A");
  output_conv_privacy (PK_friends,	I[mp_friends_privacy],	"*G*A*0*A/A");
  output_conv_privacy (PK_profile,	I[mp_profile_privacy],	"*G*A*0*A/A");
  output_conv_privacy (PK_mobile,	I[mp_m_privacy],	"*G*A*0*A/A");
  output_conv_privacy (PK_home,		I[mp_h_privacy],	"*G*A*0*A/A");
  output_conv_privacy (PK_icq,		I[mp_i_privacy],	"*G*A*0*A/A");

  adj_rec++;
}