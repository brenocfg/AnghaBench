#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  DEFCLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD5 ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_DATA ; 
 int /*<<< orphan*/  RMD160 ; 
 int /*<<< orphan*/  SHA1 ; 
 int /*<<< orphan*/  SHA256 ; 
 int /*<<< orphan*/  SHA384 ; 
 int /*<<< orphan*/  SHA512 ; 
 int /*<<< orphan*/  lib_init () ; 
 struct RClass* mrb_define_class_under (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_digest_block_length ; 
 int /*<<< orphan*/  mrb_digest_digest ; 
 int /*<<< orphan*/  mrb_digest_digest_bang ; 
 int /*<<< orphan*/  mrb_digest_digest_length ; 
 int /*<<< orphan*/  mrb_digest_hexdigest ; 
 int /*<<< orphan*/  mrb_digest_init ; 
 int /*<<< orphan*/  mrb_digest_init_copy ; 
 int /*<<< orphan*/  mrb_digest_reset ; 
 int /*<<< orphan*/  mrb_digest_update ; 
 int /*<<< orphan*/  mrb_hmac_block_length ; 
 int /*<<< orphan*/  mrb_hmac_digest ; 
 int /*<<< orphan*/  mrb_hmac_digest_length ; 
 int /*<<< orphan*/  mrb_hmac_hexdigest ; 
 int /*<<< orphan*/  mrb_hmac_init ; 
 int /*<<< orphan*/  mrb_hmac_init_copy ; 
 int /*<<< orphan*/  mrb_hmac_update ; 

void
mrb_mruby_digest_gem_init(mrb_state *mrb)
{
  struct RClass *b, *d, *h;

  lib_init();

  d = mrb_define_module(mrb, "Digest");

  b = mrb_define_class_under(mrb, d, "Base", mrb->object_class);
  mrb_define_method(mrb, b, "block_length",    mrb_digest_block_length,  MRB_ARGS_NONE());
  mrb_define_method(mrb, b, "digest",          mrb_digest_digest,        MRB_ARGS_NONE());
  mrb_define_method(mrb, b, "digest!",         mrb_digest_digest_bang,   MRB_ARGS_NONE()); /* XXX: can be defined in mrblib... */
  mrb_define_method(mrb, b, "digest_length",   mrb_digest_digest_length, MRB_ARGS_NONE());
  //mrb_define_method(mrb, b, "file",            mrb_digest_file,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, b, "hexdigest",       mrb_digest_hexdigest,     MRB_ARGS_NONE());
  //mrb_define_method(mrb, b, "hexdigest!",      mrb_digest_hexdigest_bang, MRB_ARGS_NONE()); /* XXX: can be defined in mrblib... */
  mrb_define_method(mrb, b, "initialize",      mrb_digest_init,          MRB_ARGS_NONE());
  mrb_define_method(mrb, b, "initialize_copy", mrb_digest_init_copy,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, b, "reset",           mrb_digest_reset,         MRB_ARGS_NONE());
  mrb_define_method(mrb, b, "update",          mrb_digest_update,        MRB_ARGS_REQ(1));

#define DEFCLASS(n)						\
do {								\
  struct RClass *a = mrb_define_class_under(mrb, d, #n, b);	\
  MRB_SET_INSTANCE_TT(a, MRB_TT_DATA);				\
  mrb_define_const(mrb, a, TYPESYM, mrb_fixnum_value(MD_TYPE_##n));	\
} while (0)

#ifdef HAVE_MD5
  DEFCLASS(MD5);
#endif
#ifdef HAVE_RMD160
  DEFCLASS(RMD160);
#endif
#ifdef HAVE_SHA1
  DEFCLASS(SHA1);
#endif
#ifdef HAVE_SHA256
  DEFCLASS(SHA256);
#endif
#ifdef HAVE_SHA384
  DEFCLASS(SHA384);
#endif
#ifdef HAVE_SHA512
  DEFCLASS(SHA512);
#endif

  h = mrb_define_class_under(mrb, d, "HMAC", mrb->object_class);
  MRB_SET_INSTANCE_TT(h, MRB_TT_DATA);
  mrb_define_method(mrb, h, "block_length",    mrb_hmac_block_length,  MRB_ARGS_NONE());
  mrb_define_method(mrb, h, "digest",          mrb_hmac_digest,        MRB_ARGS_NONE());
  mrb_define_method(mrb, h, "digest_length",   mrb_hmac_digest_length, MRB_ARGS_NONE());
  mrb_define_method(mrb, h, "hexdigest",       mrb_hmac_hexdigest,     MRB_ARGS_NONE());
  mrb_define_method(mrb, h, "initialize",      mrb_hmac_init,          MRB_ARGS_REQ(2));
  mrb_define_method(mrb, h, "initialize_copy", mrb_hmac_init_copy,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, h, "update",          mrb_hmac_update,        MRB_ARGS_REQ(1));
}