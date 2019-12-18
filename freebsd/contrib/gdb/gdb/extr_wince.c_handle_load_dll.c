#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int gdb_wince_len ;
typedef  int /*<<< orphan*/  dll_buf ;
struct TYPE_5__ {char* lpImageName; int /*<<< orphan*/  lpBaseOfDll; scalar_t__ fUnicode; } ;
struct TYPE_4__ {TYPE_2__ LoadDll; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_2__ LOAD_DLL_DEBUG_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* alloca (int) ; 
 TYPE_3__ current_event ; 
 int /*<<< orphan*/  current_process_handle ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  read_process_memory (int /*<<< orphan*/ ,char*,char*,int,int*) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
handle_load_dll (void *dummy)
{
  LOAD_DLL_DEBUG_INFO *event = &current_event.u.LoadDll;
  char dll_buf[MAX_PATH + 1];
  char *p, *bufp, *imgp, *dll_name, *dll_basename;
  int len;

  dll_buf[0] = dll_buf[sizeof (dll_buf) - 1] = '\0';
  if (!event->lpImageName)
    return 1;

  len = 0;
  for (bufp = dll_buf, imgp = event->lpImageName;
       bufp < dll_buf + sizeof (dll_buf);
       bufp += 16, imgp += 16)
    {
      gdb_wince_len nbytes = 0;
      (void) read_process_memory (current_process_handle,
				  imgp, bufp, 16, &nbytes);

      if (!nbytes && bufp == dll_buf)
	return 1;		/* couldn't read it */
      for (p = bufp; p < bufp + nbytes; p++)
	{
	  len++;
	  if (*p == '\0')
	    goto out;
	  if (event->fUnicode)
	    p++;
	}
      if (!nbytes)
	break;
    }

out:
  if (!len)
    return 1;
#if 0
  dll_buf[len] = '\0';
#endif
  dll_name = alloca (len);

  if (!dll_name)
    return 1;

  if (!event->fUnicode)
    memcpy (dll_name, dll_buf, len);
  else
    WideCharToMultiByte (CP_ACP, 0, (LPCWSTR) dll_buf, len,
			 dll_name, len, 0, 0);

  while ((p = strchr (dll_name, '\\')))
    *p = '/';

  /* FIXME!! It would be nice to define one symbol which pointed to the
     front of the dll if we can't find any symbols. */

  if (!(dll_basename = strrchr (dll_name, '/')))
    dll_basename = dll_name;
  else
    dll_basename++;

  /* The symbols in a dll are offset by 0x1000, which is the
     the offset from 0 of the first byte in an image - because
     of the file header and the section alignment.

     FIXME: Is this the real reason that we need the 0x1000 ? */

  printf_unfiltered ("%x:%s", event->lpBaseOfDll, dll_name);
  printf_unfiltered ("\n");

  return 1;
}