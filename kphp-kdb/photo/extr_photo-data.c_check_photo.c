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
#define  MODE_AUDIO 130 
#define  MODE_PHOTO 129 
#define  MODE_VIDEO 128 
 int /*<<< orphan*/  assert (int) ; 
 int mode ; 

int check_photo (char *photo, int photo_len) {
  if (photo_len >= 126) {
    return 0;
  }
  assert (photo_len >= 0);

  switch (mode) {
    case MODE_PHOTO:
      return 1;
    case MODE_VIDEO:
      return 1;
    case MODE_AUDIO:
      return 1;
    default:
      assert ("Unsupported mode" && 0);
  }
}