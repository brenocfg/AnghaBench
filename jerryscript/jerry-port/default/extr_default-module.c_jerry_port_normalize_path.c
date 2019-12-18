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
 int MAX_JERRY_PATH_SIZE ; 
 int PATH_MAX ; 
 int _MAX_DIR ; 
 int _MAX_DRIVE ; 
 int _MAX_PATH ; 
 char* _fullpath (char*,char*,size_t) ; 
 int /*<<< orphan*/  _splitpath_s (char*,char**,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 char* realpath (char*,char*) ; 
 int /*<<< orphan*/  strncat (char*,...) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 void* strnlen (char const*,size_t) ; 

size_t
jerry_port_normalize_path (const char *in_path_p,   /**< input file path */
                           char *out_buf_p,         /**< output buffer */
                           size_t out_buf_size,     /**< size of output buffer */
                           char *base_file_p)       /**< base file path */
{
  size_t ret = 0;

#if defined (WIN32)
  char drive[_MAX_DRIVE];
  char *dir_p = (char *) malloc (_MAX_DIR);

  char *path_p = (char *) malloc (_MAX_PATH * 2);
  *path_p = '\0';

  if (base_file_p != NULL)
  {
    _splitpath_s (base_file_p,
                  &drive,
                  _MAX_DRIVE,
                  dir_p,
                  _MAX_DIR,
                  NULL,
                  0,
                  NULL,
                  0);
    strncat (path_p, &drive, _MAX_DRIVE);
    strncat (path_p, dir_p, _MAX_DIR);
  }

  strncat (path_p, in_path_p, _MAX_PATH);

  char *norm_p = _fullpath (out_buf_p, path_p, out_buf_size);

  free (path_p);
  free (dir_p);

  if (norm_p != NULL)
  {
    ret = strnlen (norm_p, out_buf_size);
  }
#elif defined (__unix__) || defined (__APPLE__)
#define MAX_JERRY_PATH_SIZE 256
  char *buffer_p = (char *) malloc (PATH_MAX);
  char *path_p = (char *) malloc (PATH_MAX);

  char *base_p = dirname (base_file_p);
  strncpy (path_p, base_p, MAX_JERRY_PATH_SIZE);
  strncat (path_p, "/", 1);
  strncat (path_p, in_path_p, MAX_JERRY_PATH_SIZE);

  char *norm_p = realpath (path_p, buffer_p);
  free (path_p);

  if (norm_p != NULL)
  {
    const size_t len = strnlen (norm_p, out_buf_size);
    if (len < out_buf_size)
    {
      strncpy (out_buf_p, norm_p, out_buf_size);
      ret = len;
    }
  }

  free (buffer_p);
#undef MAX_JERRY_PATH_SIZE
#else
  (void) base_file_p;

  /* Do nothing, just copy the input. */
  const size_t len = strnlen (in_path_p, out_buf_size);
  if (len < out_buf_size)
  {
    strncpy (out_buf_p, in_path_p, out_buf_size);
    ret = len;
  }
#endif

  return ret;
}