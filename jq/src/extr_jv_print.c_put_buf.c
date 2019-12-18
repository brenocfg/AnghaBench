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
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 size_t MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  WriteConsoleW (int /*<<< orphan*/ ,scalar_t__*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _get_osfhandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__* jv_mem_calloc (size_t,int) ; 
 int /*<<< orphan*/  jv_string_append_buf (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void put_buf(const char *s, int len, FILE *fout, jv *strout, int is_tty) {
  if (strout) {
    *strout = jv_string_append_buf(*strout, s, len);
  } else {
#ifdef WIN32
  /* See util.h */
  if (is_tty) {
    wchar_t *ws;
    size_t wl;
    if (len == -1)
      len = strlen(s);
    wl = MultiByteToWideChar(CP_UTF8, 0, s, len, NULL, 0);
    ws = jv_mem_calloc((wl + 1), sizeof(*ws));
    if (!ws)
      return;
    wl = MultiByteToWideChar(CP_UTF8, 0, s, len, ws, wl + 1);
    ws[wl] = 0;
    WriteConsoleW((HANDLE)_get_osfhandle(fileno(fout)), ws, wl, NULL, NULL);
    free(ws);
  } else
    fwrite(s, 1, len, fout);
#else
  fwrite(s, 1, len, fout);
#endif
  }
}