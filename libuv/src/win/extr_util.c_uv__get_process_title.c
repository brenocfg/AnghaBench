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
typedef  int /*<<< orphan*/  title_w ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetConsoleTitleW (int /*<<< orphan*/ *,int) ; 
 int MAX_TITLE_LENGTH ; 
 int /*<<< orphan*/  process_title ; 
 scalar_t__ uv__convert_utf16_to_utf8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uv__get_process_title(void) {
  WCHAR title_w[MAX_TITLE_LENGTH];

  if (!GetConsoleTitleW(title_w, sizeof(title_w) / sizeof(WCHAR))) {
    return -1;
  }

  if (uv__convert_utf16_to_utf8(title_w, -1, &process_title) != 0)
    return -1;

  return 0;
}