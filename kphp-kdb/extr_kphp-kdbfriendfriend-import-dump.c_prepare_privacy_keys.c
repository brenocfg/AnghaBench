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
 int PK_album ; 
 int PK_events_invite ; 
 int PK_friends ; 
 int PK_gifts ; 
 int PK_graffiti_send ; 
 int PK_groups_invite ; 
 int PK_home ; 
 int PK_icq ; 
 int PK_mail_send ; 
 int PK_mobile ; 
 int PK_note ; 
 int PK_notecomm ; 
 int PK_photos_with ; 
 int PK_profile ; 
 int PK_video ; 
 int PK_wall_send ; 
 int crc32_str (char*) ; 

void prepare_privacy_keys (void) {
#define	PK_TWO(x,y)	{ PK_##x##_##y = (crc32_str(#x) << 32) + crc32_str("_"#y); }
#define	PK_ONE(x)	{ PK_##x = (crc32_str(#x) << 32); }
  PK_TWO (groups, invite);
  PK_TWO (events, invite);
  PK_TWO (mail, send);
  PK_TWO (wall, send);
  PK_TWO (graffiti, send);
  PK_TWO (photos, with);
  PK_ONE (friends);
  PK_ONE (profile);
  PK_ONE (mobile);
  PK_ONE (home);
  PK_ONE (icq);
  PK_ONE (gifts);
  PK_ONE (album);
  PK_ONE (note);
  PK_ONE (notecomm);
  PK_ONE (video);
#undef PK_ONE
#undef PK_TWO
}