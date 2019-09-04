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
struct tl_out_methods {int flags; int /*<<< orphan*/ * copy_through; scalar_t__ prepend_bytes; scalar_t__ (* store_get_ptr ) (scalar_t__) ;int /*<<< orphan*/  (* store_clear ) () ;} ;
typedef  enum tl_type { ____Placeholder_tl_type } tl_type ;

/* Variables and functions */
 int TLF_ALLOW_PREPEND ; 
 int /*<<< orphan*/  TL_COPY_THROUGH ; 
 scalar_t__ TL_ERRNUM ; 
 scalar_t__ TL_ERROR ; 
 size_t TL_IN_TYPE ; 
 void* TL_OUT ; 
 void* TL_OUT_EXTRA ; 
 struct tl_out_methods* TL_OUT_METHODS ; 
 scalar_t__ TL_OUT_POS ; 
 long long TL_OUT_QID ; 
 int TL_OUT_REMAINING ; 
 int* TL_OUT_SIZE ; 
 int TL_OUT_TYPE ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ stub2 (scalar_t__) ; 
 int tl_type_none ; 

__attribute__((used)) static inline int __tl_store_init (void *out, void *out_extra, enum tl_type type, struct tl_out_methods *methods, int size, int keep_error, long long qid) {
  if (TL_OUT_METHODS && TL_OUT_METHODS->store_clear) {
    TL_OUT_METHODS->store_clear ();
  }
  TL_OUT = out;
  TL_OUT_EXTRA = out_extra;
  if (out) {
    TL_OUT_METHODS = methods;
    TL_OUT_TYPE = type;
  } else {
    TL_OUT_TYPE = tl_type_none;
  }

  if (!(TL_OUT_METHODS->flags & TLF_ALLOW_PREPEND)) {
    TL_OUT_SIZE = (int *)TL_OUT_METHODS->store_get_ptr (12 + TL_OUT_METHODS->prepend_bytes);
  }
  
  if (!keep_error) {
    if (TL_ERROR) {
      free (TL_ERROR);
      TL_ERROR = 0;
      TL_ERRNUM = 0;
    }
  }
  TL_OUT_POS = 0;
  TL_OUT_QID = qid;
  TL_OUT_REMAINING = size;

  if (out) {
    TL_COPY_THROUGH = TL_OUT_METHODS ? TL_OUT_METHODS->copy_through[TL_IN_TYPE] : 0;
  } else {
    TL_COPY_THROUGH = 0;
  }
  return 0;
}