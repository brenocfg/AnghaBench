#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
struct loopinfo {void* pc0; } ;
struct TYPE_33__ {struct TYPE_33__* car; struct TYPE_33__* cdr; } ;
typedef  TYPE_2__ node ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int mrb_aspec ;
struct TYPE_34__ {int mscope; int ainfo; scalar_t__ pc; TYPE_1__* irep; int /*<<< orphan*/  mrb; } ;
typedef  TYPE_3__ codegen_scope ;
struct TYPE_32__ {int rlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOOP_BLOCK ; 
 int MRB_ARGS_BLOCK () ; 
 int MRB_ARGS_KEY (int,int) ; 
 int MRB_ARGS_OPT (int) ; 
 int MRB_ARGS_POST (int) ; 
 int MRB_ARGS_REQ (int) ; 
 int MRB_ARGS_REST () ; 
 scalar_t__ NODE_ARGS_TAIL ; 
 scalar_t__ NODE_KW_ARG ; 
 scalar_t__ NODE_MASGN ; 
 int /*<<< orphan*/  NOVAL ; 
 int /*<<< orphan*/  OP_ENTER ; 
 int /*<<< orphan*/  OP_JMP ; 
 int /*<<< orphan*/  OP_JMPIF ; 
 int /*<<< orphan*/  OP_KARG ; 
 int /*<<< orphan*/  OP_KEYEND ; 
 int /*<<< orphan*/  OP_KEY_P ; 
 int /*<<< orphan*/  OP_RETURN ; 
 int /*<<< orphan*/  VAL ; 
 int /*<<< orphan*/  codegen (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codegen_error (TYPE_3__*,char*) ; 
 int cursp () ; 
 int /*<<< orphan*/  dispatch (TYPE_3__*,int) ; 
 int /*<<< orphan*/  gen_move (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_return (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_vmassignment (TYPE_3__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int genjmp (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genjmp2 (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_0 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_2 (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_W (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  loop_pop (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct loopinfo* loop_push (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int lv_idx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 void* new_label (TYPE_3__*) ; 
 int /*<<< orphan*/  new_sym (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ nint (TYPE_2__*) ; 
 int node_len (TYPE_2__*) ; 
 int /*<<< orphan*/  nsym (TYPE_2__*) ; 
 int /*<<< orphan*/  pop () ; 
 int /*<<< orphan*/  raise_error (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  scope_finish (TYPE_3__*) ; 
 TYPE_3__* scope_new (int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int
lambda_body(codegen_scope *s, node *tree, int blk)
{
  codegen_scope *parent = s;
  s = scope_new(s->mrb, s, tree->car);
  if (s == NULL) {
    raise_error(parent, "unexpected scope");
  }

  s->mscope = !blk;

  if (blk) {
    struct loopinfo *lp = loop_push(s, LOOP_BLOCK);
    lp->pc0 = new_label(s);
  }
  tree = tree->cdr;
  if (tree->car == NULL) {
    genop_W(s, OP_ENTER, 0);
  }
  else {
    mrb_aspec a;
    int ma, oa, ra, pa, ka, kd, ba;
    int pos, i;
    node *opt;
    node *margs, *pargs;
    node *tail;

    /* mandatory arguments */
    ma = node_len(tree->car->car);
    margs = tree->car->car;
    tail = tree->car->cdr->cdr->cdr->cdr;

    /* optional arguments */
    oa = node_len(tree->car->cdr->car);
    /* rest argument? */
    ra = tree->car->cdr->cdr->car ? 1 : 0;
    /* mandatory arugments after rest argument */
    pa = node_len(tree->car->cdr->cdr->cdr->car);
    pargs = tree->car->cdr->cdr->cdr->car;
    /* keyword arguments */
    ka = tail? node_len(tail->cdr->car) : 0;
    /* keyword dictionary? */
    kd = tail && tail->cdr->cdr->car? 1 : 0;
    /* block argument? */
    ba = tail && tail->cdr->cdr->cdr->car ? 1 : 0;

    if (ma > 0x1f || oa > 0x1f || pa > 0x1f || ka > 0x1f) {
      codegen_error(s, "too many formal arguments");
    }
    a = MRB_ARGS_REQ(ma)
      | MRB_ARGS_OPT(oa)
      | (ra? MRB_ARGS_REST() : 0)
      | MRB_ARGS_POST(pa)
      | MRB_ARGS_KEY(ka, kd)
      | (ba? MRB_ARGS_BLOCK() : 0);
    s->ainfo = (((ma+oa) & 0x3f) << 7) /* (12bits = 5:1:5:1) */
      | ((ra & 0x1) << 6)
      | ((pa & 0x1f) << 1)
      | (kd & 0x1);
    genop_W(s, OP_ENTER, a);
    /* generate jump table for optional arguments initializer */
    pos = new_label(s);
    for (i=0; i<oa; i++) {
      new_label(s);
      genjmp(s, OP_JMP, 0);
    }
    if (oa > 0) {
      genjmp(s, OP_JMP, 0);
    }
    opt = tree->car->cdr->car;
    i = 0;
    while (opt) {
      int idx;

      dispatch(s, pos+i*3+1);
      codegen(s, opt->car->cdr, VAL);
      pop();
      idx = lv_idx(s, nsym(opt->car->car));
      gen_move(s, idx, cursp(), 0);
      i++;
      opt = opt->cdr;
    }
    if (oa > 0) {
      dispatch(s, pos+i*3+1);
    }

    /* keyword arguments */
    if (tail) {
      node *kwds = tail->cdr->car;
      int kwrest = 0;

      if (tail->cdr->cdr->car) {
        kwrest = 1;
      }
      mrb_assert(nint(tail->car) == NODE_ARGS_TAIL);
      mrb_assert(node_len(tail) == 4);

      while (kwds) {
        int jmpif_key_p, jmp_def_set = -1;
        node *kwd = kwds->car, *def_arg = kwd->cdr->cdr->car;
        mrb_sym kwd_sym = nsym(kwd->cdr->car);

        mrb_assert(nint(kwd->car) == NODE_KW_ARG);

        if (def_arg) {
          genop_2(s, OP_KEY_P, cursp(), new_sym(s, kwd_sym));
          jmpif_key_p = genjmp2(s, OP_JMPIF, cursp(), 0, 0);
          codegen(s, def_arg, VAL);
          pop();
          gen_move(s, lv_idx(s, kwd_sym), cursp(), 0);
          jmp_def_set = genjmp(s, OP_JMP, 0);
          dispatch(s, jmpif_key_p);
        }
        genop_2(s, OP_KARG, lv_idx(s, kwd_sym), new_sym(s, kwd_sym));
        if (jmp_def_set != -1) {
          dispatch(s, jmp_def_set);
        }
        i++;

        kwds = kwds->cdr;
      }
      if (tail->cdr->car && !kwrest) {
        genop_0(s, OP_KEYEND);
      }
    }

    /* argument destructuring */
    if (margs) {
      node *n = margs;

      pos = 1;
      while (n) {
        if (nint(n->car->car) == NODE_MASGN) {
          gen_vmassignment(s, n->car->cdr->car, pos, NOVAL);
        }
        pos++;
        n = n->cdr;
      }
    }
    if (pargs) {
      node *n = margs;

      pos = ma+oa+ra+1;
      while (n) {
        if (nint(n->car->car) == NODE_MASGN) {
          gen_vmassignment(s, n->car->cdr->car, pos, NOVAL);
        }
        pos++;
        n = n->cdr;
      }
    }
  }

  codegen(s, tree->cdr->car, VAL);
  pop();
  if (s->pc > 0) {
    gen_return(s, OP_RETURN, cursp());
  }
  if (blk) {
    loop_pop(s, NOVAL);
  }
  scope_finish(s);
  return parent->irep->rlen - 1;
}