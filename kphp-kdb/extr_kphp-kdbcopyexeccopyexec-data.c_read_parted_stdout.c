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
struct stat {int st_size; } ;
struct TYPE_3__ {void* buf; int size; int cutted_size; } ;
typedef  TYPE_1__ parted_output_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fd_close (int*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ lseek (int,int const,int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int max_output_size ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 int const read (int,void*,int const) ; 

__attribute__((used)) static int read_parted_stdout (int fd, parted_output_t *O) {
  O->buf = NULL;
  O->size = 0;
  O->cutted_size = 0;

  struct stat st;
  if (fstat (fd, &st) < 0) {
    fd_close (&fd);
    return -__LINE__;
  }
  O->size = st.st_size;
  O->cutted_size = (O->size <= max_output_size) ? (O->size) : max_output_size;
  O->buf = malloc (O->cutted_size);
  if (O->buf == NULL) {
    fd_close (&fd);
    return -__LINE__;
  }
  if (lseek (fd, 0, SEEK_SET) != 0) {
    free (O->buf);
    fd_close (&fd);
    return -__LINE__;
  }
  if (O->size <= max_output_size) {
    if (read (fd, O->buf, O->cutted_size) != O->cutted_size) {
      O->cutted_size = 0;
      free (O->buf);
      O->buf = NULL;
      fd_close (&fd);
      return -__LINE__;
    }
  } else {
    const int head_size = (max_output_size - 5) >> 1, tail_size = (max_output_size - 5) - head_size;
    void *b = O->buf;
    if (read (fd, b, head_size) != head_size) {
      O->cutted_size = 0;
      free (O->buf);
      O->buf = NULL;
      fd_close (&fd);
      return -__LINE__;
    }
    if (lseek (fd, -tail_size, SEEK_END) == (off_t) -1) {
      O->cutted_size = 0;
      free (O->buf);
      O->buf = NULL;
      fd_close (&fd);
      return -__LINE__;
    }

    b += head_size;
    memcpy (b, "\n...\n", 5);
    b += 5;
    if (read (fd, b, tail_size) != tail_size) {
      O->cutted_size = 0;
      free (O->buf);
      O->buf = NULL;
      fd_close (&fd);
      return -__LINE__;
    }
  }
  fd_close (&fd);
  return 0;
}