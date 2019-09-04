#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct mrb_parser_heredoc_info {struct mrb_ast_node* doc; } ;
struct mrb_ast_node {scalar_t__ filename_index; struct mrb_ast_node* cdr; struct mrb_ast_node* car; int /*<<< orphan*/  lineno; } ;
struct loopinfo {int pc0; int pc1; void* type; int pc2; int ensure_level; struct loopinfo* prev; } ;
typedef  struct mrb_ast_node node ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  double mrb_float ;
typedef  int /*<<< orphan*/  mrb_bool ;
struct TYPE_40__ {int rlev; scalar_t__ filename_index; int ensure_level; int ainfo; int /*<<< orphan*/ * mrb; struct TYPE_40__* prev; struct loopinfo* loop; int /*<<< orphan*/  mscope; int /*<<< orphan*/  lineno; int /*<<< orphan*/  parser; void* filename; int /*<<< orphan*/  pc; int /*<<< orphan*/  debug_start_pos; int /*<<< orphan*/  lines; TYPE_1__* irep; } ;
typedef  TYPE_2__ codegen_scope ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_39__ {int /*<<< orphan*/  debug_info; } ;

/* Variables and functions */
 int CALL_MAXARGS ; 
 int /*<<< orphan*/  FALSE ; 
 void* LOOP_BEGIN ; 
 void* LOOP_NORMAL ; 
 void* LOOP_RESCUE ; 
 int MRB_CODEGEN_LEVEL_MAX ; 
#define  NODE_ALIAS 198 
#define  NODE_AND 197 
#define  NODE_ARG 196 
#define  NODE_ARRAY 195 
#define  NODE_ASGN 194 
#define  NODE_BACK_REF 193 
#define  NODE_BEGIN 192 
#define  NODE_BLOCK 191 
#define  NODE_BLOCK_ARG 190 
#define  NODE_BREAK 189 
#define  NODE_CALL 188 
#define  NODE_CASE 187 
#define  NODE_CLASS 186 
#define  NODE_COLON2 185 
#define  NODE_COLON3 184 
#define  NODE_CONST 183 
#define  NODE_CVAR 182 
#define  NODE_DEF 181 
#define  NODE_DEFINED 180 
#define  NODE_DOT2 179 
#define  NODE_DOT3 178 
#define  NODE_DREGX 177 
#define  NODE_DSTR 176 
#define  NODE_DSYM 175 
#define  NODE_DXSTR 174 
#define  NODE_ENSURE 173 
#define  NODE_FALSE 172 
#define  NODE_FCALL 171 
#define  NODE_FLOAT 170 
#define  NODE_FOR 169 
#define  NODE_GVAR 168 
#define  NODE_HASH 167 
#define  NODE_HEREDOC 166 
#define  NODE_IF 165 
#define  NODE_INT 164 
#define  NODE_IVAR 163 
#define  NODE_KW_HASH 162 
 int const NODE_KW_REST_ARGS ; 
#define  NODE_LAMBDA 161 
#define  NODE_LVAR 160 
#define  NODE_MASGN 159 
#define  NODE_MODULE 158 
#define  NODE_NEGATE 157 
#define  NODE_NEXT 156 
#define  NODE_NIL 155 
#define  NODE_NTH_REF 154 
#define  NODE_OP_ASGN 153 
#define  NODE_OR 152 
#define  NODE_POSTEXE 151 
#define  NODE_REDO 150 
#define  NODE_REGX 149 
#define  NODE_RESCUE 148 
#define  NODE_RETRY 147 
#define  NODE_RETURN 146 
#define  NODE_SCALL 145 
#define  NODE_SCLASS 144 
#define  NODE_SCOPE 143 
#define  NODE_SDEF 142 
#define  NODE_SELF 141 
#define  NODE_SPLAT 140 
#define  NODE_STR 139 
#define  NODE_SUPER 138 
#define  NODE_SYM 137 
#define  NODE_SYMBOLS 136 
#define  NODE_TRUE 135 
#define  NODE_UNDEF 134 
#define  NODE_UNTIL 133 
#define  NODE_WHILE 132 
#define  NODE_WORDS 131 
#define  NODE_XSTR 130 
#define  NODE_YIELD 129 
#define  NODE_ZSUPER 128 
 int NOVAL ; 
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  OP_ALIAS ; 
 int /*<<< orphan*/  OP_ARGARY ; 
 int /*<<< orphan*/  OP_ARRAY ; 
 int /*<<< orphan*/  OP_ARRAY2 ; 
 scalar_t__ OP_ARYPUSH ; 
 int /*<<< orphan*/  OP_BLKPUSH ; 
 int /*<<< orphan*/  OP_BLOCK ; 
 int /*<<< orphan*/  OP_CLASS ; 
 int /*<<< orphan*/  OP_DEF ; 
 scalar_t__ OP_DIV ; 
 scalar_t__ OP_EPOP ; 
 scalar_t__ OP_EPUSH ; 
 scalar_t__ OP_EXCEPT ; 
 int /*<<< orphan*/  OP_EXEC ; 
 scalar_t__ OP_GE ; 
 int /*<<< orphan*/  OP_GETCONST ; 
 int /*<<< orphan*/  OP_GETCV ; 
 int /*<<< orphan*/  OP_GETGV ; 
 int /*<<< orphan*/  OP_GETIV ; 
 int /*<<< orphan*/  OP_GETMCNST ; 
 int /*<<< orphan*/  OP_GETUPVAR ; 
 scalar_t__ OP_GT ; 
 int /*<<< orphan*/  OP_HASH ; 
 int /*<<< orphan*/  OP_HASHADD ; 
 scalar_t__ OP_HASHCAT ; 
 int /*<<< orphan*/  OP_JMP ; 
 int /*<<< orphan*/  OP_JMPIF ; 
 int /*<<< orphan*/  OP_JMPNOT ; 
 int /*<<< orphan*/  OP_LAMBDA ; 
 scalar_t__ OP_LE ; 
 scalar_t__ OP_LOADF ; 
 int /*<<< orphan*/  OP_LOADI ; 
 int /*<<< orphan*/  OP_LOADINEG ; 
 scalar_t__ OP_LOADI_0 ; 
 scalar_t__ OP_LOADI__1 ; 
 int /*<<< orphan*/  OP_LOADL ; 
 scalar_t__ OP_LOADNIL ; 
 scalar_t__ OP_LOADSELF ; 
 int /*<<< orphan*/  OP_LOADSYM ; 
 scalar_t__ OP_LOADT ; 
 scalar_t__ OP_LT ; 
 int /*<<< orphan*/  OP_METHOD ; 
 int /*<<< orphan*/  OP_MODULE ; 
 scalar_t__ OP_MUL ; 
 int /*<<< orphan*/  OP_NOP ; 
 scalar_t__ OP_OCLASS ; 
 int /*<<< orphan*/  OP_ONERR ; 
 scalar_t__ OP_POPERR ; 
 scalar_t__ OP_RAISE ; 
 scalar_t__ OP_RANGE_EXC ; 
 scalar_t__ OP_RANGE_INC ; 
 int /*<<< orphan*/  OP_RESCUE ; 
 int /*<<< orphan*/  OP_RETURN ; 
 int /*<<< orphan*/  OP_RETURN_BLK ; 
 scalar_t__ OP_SCLASS ; 
 int /*<<< orphan*/  OP_SEND ; 
 scalar_t__ OP_STRCAT ; 
 int /*<<< orphan*/  OP_STRING ; 
 int /*<<< orphan*/  OP_SUB ; 
 int /*<<< orphan*/  OP_SUPER ; 
 scalar_t__ OP_TCLASS ; 
 scalar_t__ OP_UNDEF ; 
 char* REGEXP_CLASS ; 
 int /*<<< orphan*/  TRUE ; 
 int VAL ; 
 int /*<<< orphan*/  attrsym (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codegen_error (TYPE_2__*,char*) ; 
 int cursp () ; 
 int /*<<< orphan*/  dispatch (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dispatch_linked (TYPE_2__*,int) ; 
 int /*<<< orphan*/  for_body (TYPE_2__*,struct mrb_ast_node*) ; 
 int /*<<< orphan*/  gen_addsub (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_assignment (TYPE_2__*,struct mrb_ast_node*,int,int) ; 
 int /*<<< orphan*/  gen_call (TYPE_2__*,struct mrb_ast_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gen_intern (TYPE_2__*) ; 
 int /*<<< orphan*/  gen_literal_array (TYPE_2__*,struct mrb_ast_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_move (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  gen_return (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_retval (TYPE_2__*,struct mrb_ast_node*) ; 
 int gen_values (TYPE_2__*,struct mrb_ast_node*,int,int) ; 
 int /*<<< orphan*/  gen_vmassignment (TYPE_2__*,struct mrb_ast_node*,int,int) ; 
 void* genjmp (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int genjmp2 (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  genop_0 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_1 (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  genop_2 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  genop_2S (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  genop_3 (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 
 int lambda_body (TYPE_2__*,struct mrb_ast_node*,int) ; 
 int /*<<< orphan*/  loop_break (TYPE_2__*,struct mrb_ast_node*) ; 
 int /*<<< orphan*/  loop_pop (TYPE_2__*,int) ; 
 struct loopinfo* loop_push (TYPE_2__*,void*) ; 
 int lv_idx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int /*<<< orphan*/  mrb_debug_info_append_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 double mrb_float_read (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_float_value (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  mrb_format (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_intern (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_intern_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* mrb_parser_get_filename (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 
 char* mrb_sym2name_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 char nchar (struct mrb_ast_node*) ; 
 void* new_label (TYPE_2__*) ; 
 int new_lit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int new_sym (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int const nint (struct mrb_ast_node*) ; 
 int /*<<< orphan*/  nosplat (struct mrb_ast_node*) ; 
 int /*<<< orphan*/  nsym (struct mrb_ast_node*) ; 
 int /*<<< orphan*/  on_eval (TYPE_2__*) ; 
 int /*<<< orphan*/  pop () ; 
 int /*<<< orphan*/  pop_n (int) ; 
 int /*<<< orphan*/  push () ; 
 int /*<<< orphan*/  push_n (int) ; 
 int /*<<< orphan*/  raise_error (TYPE_2__*,char const*) ; 
 double readint_float (TYPE_2__*,char*,int) ; 
 int readint_mrb_int (TYPE_2__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int scope_body (TYPE_2__*,struct mrb_ast_node*,int) ; 

__attribute__((used)) static void
codegen(codegen_scope *s, node *tree, int val)
{
  int nt;
  int rlev = s->rlev;

  if (!tree) {
    if (val) {
      genop_1(s, OP_LOADNIL, cursp());
      push();
    }
    return;
  }

  s->rlev++;
  if (s->rlev > MRB_CODEGEN_LEVEL_MAX) {
    codegen_error(s, "too complex expression");
  }
  if (s->irep && s->filename_index != tree->filename_index) {
    const char *filename = mrb_parser_get_filename(s->parser, s->filename_index);

    mrb_debug_info_append_file(s->mrb, s->irep->debug_info,
                               filename, s->lines, s->debug_start_pos, s->pc);
    s->debug_start_pos = s->pc;
    s->filename_index = tree->filename_index;
    s->filename = mrb_parser_get_filename(s->parser, tree->filename_index);
  }

  nt = nint(tree->car);
  s->lineno = tree->lineno;
  tree = tree->cdr;
  switch (nt) {
  case NODE_BEGIN:
    if (val && !tree) {
      genop_1(s, OP_LOADNIL, cursp());
      push();
    }
    while (tree) {
      codegen(s, tree->car, tree->cdr ? NOVAL : val);
      tree = tree->cdr;
    }
    break;

  case NODE_RESCUE:
    {
      int noexc, exend, pos1, pos2, tmp;
      struct loopinfo *lp;

      if (tree->car == NULL) goto exit;
      lp = loop_push(s, LOOP_BEGIN);
      lp->pc0 = new_label(s);
      lp->pc1 = genjmp(s, OP_ONERR, 0);
      codegen(s, tree->car, VAL);
      pop();
      lp->type = LOOP_RESCUE;
      noexc = genjmp(s, OP_JMP, 0);
      dispatch(s, lp->pc1);
      tree = tree->cdr;
      exend = 0;
      pos1 = 0;
      if (tree->car) {
        node *n2 = tree->car;
        int exc = cursp();

        genop_1(s, OP_EXCEPT, exc);
        push();
        while (n2) {
          node *n3 = n2->car;
          node *n4 = n3->car;

          if (pos1) dispatch(s, pos1);
          pos2 = 0;
          do {
            if (n4 && n4->car && nint(n4->car->car) == NODE_SPLAT) {
              codegen(s, n4->car, VAL);
              gen_move(s, cursp(), exc, 0);
              push_n(2); pop_n(2); /* space for one arg and a block */
              pop();
              genop_3(s, OP_SEND, cursp(), new_sym(s, mrb_intern_lit(s->mrb, "__case_eqq")), 1);
            }
            else {
              if (n4) {
                codegen(s, n4->car, VAL);
              }
              else {
                genop_2(s, OP_GETCONST, cursp(), new_sym(s, mrb_intern_lit(s->mrb, "StandardError")));
                push();
              }
              pop();
              genop_2(s, OP_RESCUE, exc, cursp());
            }
            tmp = genjmp2(s, OP_JMPIF, cursp(), pos2, val);
            pos2 = tmp;
            if (n4) {
              n4 = n4->cdr;
            }
          } while (n4);
          pos1 = genjmp(s, OP_JMP, 0);
          dispatch_linked(s, pos2);

          pop();
          if (n3->cdr->car) {
            gen_assignment(s, n3->cdr->car, exc, NOVAL);
          }
          if (n3->cdr->cdr->car) {
            codegen(s, n3->cdr->cdr->car, val);
            if (val) pop();
          }
          tmp = genjmp(s, OP_JMP, exend);
          exend = tmp;
          n2 = n2->cdr;
          push();
        }
        if (pos1) {
          dispatch(s, pos1);
          genop_1(s, OP_RAISE, exc);
        }
      }
      pop();
      tree = tree->cdr;
      dispatch(s, noexc);
      genop_1(s, OP_POPERR, 1);
      if (tree->car) {
        codegen(s, tree->car, val);
      }
      else if (val) {
        push();
      }
      dispatch_linked(s, exend);
      loop_pop(s, NOVAL);
    }
    break;

  case NODE_ENSURE:
    if (!tree->cdr || !tree->cdr->cdr ||
        (nint(tree->cdr->cdr->car) == NODE_BEGIN &&
         tree->cdr->cdr->cdr)) {
      int idx;

      s->ensure_level++;
      idx = scope_body(s, tree->cdr, NOVAL);
      genop_1(s, OP_EPUSH, idx);
      codegen(s, tree->car, val);
      s->ensure_level--;
      genop_1(s, OP_EPOP, 1);
    }
    else {                      /* empty ensure ignored */
      codegen(s, tree->car, val);
    }
    break;

  case NODE_LAMBDA:
    if (val) {
      int idx = lambda_body(s, tree, 1);

      genop_2(s, OP_LAMBDA, cursp(), idx);
      push();
    }
    break;

  case NODE_BLOCK:
    if (val) {
      int idx = lambda_body(s, tree, 1);

      genop_2(s, OP_BLOCK, cursp(), idx);
      push();
    }
    break;

  case NODE_IF:
    {
      int pos1, pos2;
      node *elsepart = tree->cdr->cdr->car;

      if (!tree->car) {
        codegen(s, elsepart, val);
        goto exit;
      }
      switch (nint(tree->car->car)) {
      case NODE_TRUE:
      case NODE_INT:
      case NODE_STR:
        codegen(s, tree->cdr->car, val);
        goto exit;
      case NODE_FALSE:
      case NODE_NIL:
        codegen(s, elsepart, val);
        goto exit;
      }
      codegen(s, tree->car, VAL);
      pop();
      pos1 = genjmp2(s, OP_JMPNOT, cursp(), 0, val);

      codegen(s, tree->cdr->car, val);
      if (elsepart) {
        if (val) pop();
        pos2 = genjmp(s, OP_JMP, 0);
        dispatch(s, pos1);
        codegen(s, elsepart, val);
        dispatch(s, pos2);
      }
      else {
        if (val) {
          pop();
          pos2 = genjmp(s, OP_JMP, 0);
          dispatch(s, pos1);
          genop_1(s, OP_LOADNIL, cursp());
          dispatch(s, pos2);
          push();
        }
        else {
          dispatch(s, pos1);
        }
      }
    }
    break;

  case NODE_AND:
    {
      int pos;

      codegen(s, tree->car, VAL);
      pop();
      pos = genjmp2(s, OP_JMPNOT, cursp(), 0, val);
      codegen(s, tree->cdr, val);
      dispatch(s, pos);
    }
    break;

  case NODE_OR:
    {
      int pos;

      codegen(s, tree->car, VAL);
      pop();
      pos = genjmp2(s, OP_JMPIF, cursp(), 0, val);
      codegen(s, tree->cdr, val);
      dispatch(s, pos);
    }
    break;

  case NODE_WHILE:
    {
      struct loopinfo *lp = loop_push(s, LOOP_NORMAL);

      lp->pc0 = new_label(s);
      lp->pc1 = genjmp(s, OP_JMP, 0);
      lp->pc2 = new_label(s);
      codegen(s, tree->cdr, NOVAL);
      dispatch(s, lp->pc1);
      codegen(s, tree->car, VAL);
      pop();
      genjmp2(s, OP_JMPIF, cursp(), lp->pc2, NOVAL);

      loop_pop(s, val);
    }
    break;

  case NODE_UNTIL:
    {
      struct loopinfo *lp = loop_push(s, LOOP_NORMAL);

      lp->pc0 = new_label(s);
      lp->pc1 = genjmp(s, OP_JMP, 0);
      lp->pc2 = new_label(s);
      codegen(s, tree->cdr, NOVAL);
      dispatch(s, lp->pc1);
      codegen(s, tree->car, VAL);
      pop();
      genjmp2(s, OP_JMPNOT, cursp(), lp->pc2, NOVAL);

      loop_pop(s, val);
    }
    break;

  case NODE_FOR:
    for_body(s, tree);
    if (val) push();
    break;

  case NODE_CASE:
    {
      int head = 0;
      int pos1, pos2, pos3, tmp;
      node *n;

      pos3 = 0;
      if (tree->car) {
        head = cursp();
        codegen(s, tree->car, VAL);
      }
      tree = tree->cdr;
      while (tree) {
        n = tree->car->car;
        pos1 = pos2 = 0;
        while (n) {
          codegen(s, n->car, VAL);
          if (head) {
            gen_move(s, cursp(), head, 0);
            push(); push(); pop(); pop(); pop();
            if (nint(n->car->car) == NODE_SPLAT) {
              genop_3(s, OP_SEND, cursp(), new_sym(s, mrb_intern_lit(s->mrb, "__case_eqq")), 1);
            }
            else {
              genop_3(s, OP_SEND, cursp(), new_sym(s, mrb_intern_lit(s->mrb, "===")), 1);
            }
          }
          else {
            pop();
          }
          tmp = genjmp2(s, OP_JMPIF, cursp(), pos2, NOVAL);
          pos2 = tmp;
          n = n->cdr;
        }
        if (tree->car->car) {
          pos1 = genjmp(s, OP_JMP, 0);
          dispatch_linked(s, pos2);
        }
        codegen(s, tree->car->cdr, val);
        if (val) pop();
        tmp = genjmp(s, OP_JMP, pos3);
        pos3 = tmp;
        if (pos1) dispatch(s, pos1);
        tree = tree->cdr;
      }
      if (val) {
        int pos = cursp();
        genop_1(s, OP_LOADNIL, cursp());
        if (pos3) dispatch_linked(s, pos3);
        if (head) pop();
        if (cursp() != pos) {
          gen_move(s, cursp(), pos, 0);
        }
        push();
      }
      else {
        if (pos3) {
          dispatch_linked(s, pos3);
        }
        if (head) {
          pop();
        }
      }
    }
    break;

  case NODE_SCOPE:
    scope_body(s, tree, NOVAL);
    break;

  case NODE_FCALL:
  case NODE_CALL:
    gen_call(s, tree, 0, 0, val, 0);
    break;
  case NODE_SCALL:
    gen_call(s, tree, 0, 0, val, 1);
    break;

  case NODE_DOT2:
    codegen(s, tree->car, val);
    codegen(s, tree->cdr, val);
    if (val) {
      pop(); pop();
      genop_1(s, OP_RANGE_INC, cursp());
      push();
    }
    break;

  case NODE_DOT3:
    codegen(s, tree->car, val);
    codegen(s, tree->cdr, val);
    if (val) {
      pop(); pop();
      genop_1(s, OP_RANGE_EXC, cursp());
      push();
    }
    break;

  case NODE_COLON2:
    {
      int sym = new_sym(s, nsym(tree->cdr));

      codegen(s, tree->car, VAL);
      pop();
      genop_2(s, OP_GETMCNST, cursp(), sym);
      if (val) push();
    }
    break;

  case NODE_COLON3:
    {
      int sym = new_sym(s, nsym(tree));

      genop_1(s, OP_OCLASS, cursp());
      genop_2(s, OP_GETMCNST, cursp(), sym);
      if (val) push();
    }
    break;

  case NODE_ARRAY:
    {
      int n;

      n = gen_values(s, tree, val, 0);
      if (n >= 0) {
        if (val) {
          pop_n(n);
          genop_2(s, OP_ARRAY, cursp(), n);
          push();
        }
      }
      else if (val) {
        push();
      }
    }
    break;

  case NODE_HASH:
  case NODE_KW_HASH:
    {
      int len = 0;
      mrb_bool update = FALSE;

      while (tree) {
        if (nint(tree->car->car->car) == NODE_KW_REST_ARGS) {
          if (len > 0) {
            pop_n(len*2);
            if (!update) {
              genop_2(s, OP_HASH, cursp(), len);
            }
            else {
              pop();
              genop_2(s, OP_HASHADD, cursp(), len);
            }
            push();
          }
          codegen(s, tree->car->cdr, VAL);
          if (len > 0 || update) {
            pop(); pop();
            genop_1(s, OP_HASHCAT, cursp());
            push();
          }
          update = TRUE;
          len = 0;
        }
        else {
          codegen(s, tree->car->car, val);
          codegen(s, tree->car->cdr, val);
          len++;
        }
        tree = tree->cdr;
        if (val && len == 255) {
          pop_n(len*2);
          if (!update) {
            genop_2(s, OP_HASH, cursp(), len);
          }
          else {
            pop();
            genop_2(s, OP_HASHADD, cursp(), len);
          }
          push();
          update = TRUE;
          len = 0;
        }
      }
      if (val) {
        pop_n(len*2);
        if (!update) {
          genop_2(s, OP_HASH, cursp(), len);
        }
        else {
          pop();
          if (len > 0) {
            genop_2(s, OP_HASHADD, cursp(), len);
          }
        }
        push();
      }
    }
    break;

  case NODE_SPLAT:
    codegen(s, tree, val);
    break;

  case NODE_ASGN:
    codegen(s, tree->cdr, VAL);
    pop();
    gen_assignment(s, tree->car, cursp(), val);
    break;

  case NODE_MASGN:
    {
      int len = 0, n = 0, post = 0;
      node *t = tree->cdr, *p;
      int rhs = cursp();

      if (nint(t->car) == NODE_ARRAY && t->cdr && nosplat(t->cdr)) {
        /* fixed rhs */
        t = t->cdr;
        while (t) {
          codegen(s, t->car, VAL);
          len++;
          t = t->cdr;
        }
        tree = tree->car;
        if (tree->car) {                /* pre */
          t = tree->car;
          n = 0;
          while (t) {
            if (n < len) {
              gen_assignment(s, t->car, rhs+n, NOVAL);
              n++;
            }
            else {
              genop_1(s, OP_LOADNIL, rhs+n);
              gen_assignment(s, t->car, rhs+n, NOVAL);
            }
            t = t->cdr;
          }
        }
        t = tree->cdr;
        if (t) {
          if (t->cdr) {         /* post count */
            p = t->cdr->car;
            while (p) {
              post++;
              p = p->cdr;
            }
          }
          if (t->car) {         /* rest (len - pre - post) */
            int rn;

            if (len < post + n) {
              rn = 0;
            }
            else {
              rn = len - post - n;
            }
            genop_3(s, OP_ARRAY2, cursp(), rhs+n, rn);
            gen_assignment(s, t->car, cursp(), NOVAL);
            n += rn;
          }
          if (t->cdr && t->cdr->car) {
            t = t->cdr->car;
            while (n<len) {
              gen_assignment(s, t->car, rhs+n, NOVAL);
              t = t->cdr;
              n++;
            }
          }
        }
        pop_n(len);
        if (val) {
          genop_2(s, OP_ARRAY, rhs, len);
          push();
        }
      }
      else {
        /* variable rhs */
        codegen(s, t, VAL);
        gen_vmassignment(s, tree->car, rhs, val);
        if (!val) {
          pop();
        }
      }
    }
    break;

  case NODE_OP_ASGN:
    {
      mrb_sym sym = nsym(tree->cdr->car);
      mrb_int len;
      const char *name = mrb_sym2name_len(s->mrb, sym, &len);
      int idx, callargs = -1, vsp = -1;

      if ((len == 2 && name[0] == '|' && name[1] == '|') &&
          (nint(tree->car->car) == NODE_CONST ||
           nint(tree->car->car) == NODE_CVAR)) {
        int onerr, noexc, exc;
        struct loopinfo *lp;

        onerr = genjmp(s, OP_ONERR, 0);
        lp = loop_push(s, LOOP_BEGIN);
        lp->pc1 = onerr;
        exc = cursp();
        codegen(s, tree->car, VAL);
        lp->type = LOOP_RESCUE;
        genop_1(s, OP_POPERR, 1);
        noexc = genjmp(s, OP_JMP, 0);
        dispatch(s, onerr);
        genop_1(s, OP_EXCEPT, exc);
        genop_1(s, OP_LOADF, exc);
        dispatch(s, noexc);
        loop_pop(s, NOVAL);
      }
      else if (nint(tree->car->car) == NODE_CALL) {
        node *n = tree->car->cdr;
        int base, i, nargs = 0;
        callargs = 0;

        if (val) {
          vsp = cursp();
          push();
        }
        codegen(s, n->car, VAL);   /* receiver */
        idx = new_sym(s, nsym(n->cdr->car));
        base = cursp()-1;
        if (n->cdr->cdr->car) {
          nargs = gen_values(s, n->cdr->cdr->car->car, VAL, 1);
          if (nargs >= 0) {
            callargs = nargs;
          }
          else { /* varargs */
            push();
            nargs = 1;
            callargs = CALL_MAXARGS;
          }
        }
        /* copy receiver and arguments */
        gen_move(s, cursp(), base, 1);
        for (i=0; i<nargs; i++) {
          gen_move(s, cursp()+i+1, base+i+1, 1);
        }
        push_n(nargs+2);pop_n(nargs+2); /* space for receiver, arguments and a block */
        genop_3(s, OP_SEND, cursp(), idx, callargs);
        push();
      }
      else {
        codegen(s, tree->car, VAL);
      }
      if (len == 2 &&
          ((name[0] == '|' && name[1] == '|') ||
           (name[0] == '&' && name[1] == '&'))) {
        int pos;

        pop();
        if (val) {
          if (vsp >= 0) {
            gen_move(s, vsp, cursp(), 1);
          }
          pos = genjmp2(s, name[0]=='|'?OP_JMPIF:OP_JMPNOT, cursp(), 0, val);
        }
        else {
          pos = genjmp2(s, name[0]=='|'?OP_JMPIF:OP_JMPNOT, cursp(), 0, val);
        }
        codegen(s, tree->cdr->cdr->car, VAL);
        pop();
        if (val && vsp >= 0) {
          gen_move(s, vsp, cursp(), 1);
        }
        if (nint(tree->car->car) == NODE_CALL) {
          if (callargs == CALL_MAXARGS) {
            pop();
            genop_1(s, OP_ARYPUSH, cursp());
          }
          else {
            pop_n(callargs);
            callargs++;
          }
          pop();
          idx = new_sym(s, attrsym(s, nsym(tree->car->cdr->cdr->car)));
          genop_3(s, OP_SEND, cursp(), idx, callargs);
        }
        else {
          gen_assignment(s, tree->car, cursp(), val);
        }
        dispatch(s, pos);
        goto exit;
      }
      codegen(s, tree->cdr->cdr->car, VAL);
      push(); pop();
      pop(); pop();

      if (len == 1 && name[0] == '+')  {
        gen_addsub(s, OP_ADD, cursp());
      }
      else if (len == 1 && name[0] == '-')  {
        gen_addsub(s, OP_SUB, cursp());
      }
      else if (len == 1 && name[0] == '*')  {
        genop_1(s, OP_MUL, cursp());
      }
      else if (len == 1 && name[0] == '/')  {
        genop_1(s, OP_DIV, cursp());
      }
      else if (len == 1 && name[0] == '<')  {
        genop_1(s, OP_LT, cursp());
      }
      else if (len == 2 && name[0] == '<' && name[1] == '=')  {
        genop_1(s, OP_LE, cursp());
      }
      else if (len == 1 && name[0] == '>')  {
        genop_1(s, OP_GT, cursp());
      }
      else if (len == 2 && name[0] == '>' && name[1] == '=')  {
        genop_1(s, OP_GE, cursp());
      }
      else {
        idx = new_sym(s, sym);
        genop_3(s, OP_SEND, cursp(), idx, 1);
      }
      if (callargs < 0) {
        gen_assignment(s, tree->car, cursp(), val);
      }
      else {
        if (val && vsp >= 0) {
          gen_move(s, vsp, cursp(), 0);
        }
        if (callargs == CALL_MAXARGS) {
          pop();
          genop_1(s, OP_ARYPUSH, cursp());
        }
        else {
          pop_n(callargs);
          callargs++;
        }
        pop();
        idx = new_sym(s, attrsym(s,nsym(tree->car->cdr->cdr->car)));
        genop_3(s, OP_SEND, cursp(), idx, callargs);
      }
    }
    break;

  case NODE_SUPER:
    {
      codegen_scope *s2 = s;
      int lv = 0;
      int n = 0, noop = 0, sendv = 0;

      push();        /* room for receiver */
      while (!s2->mscope) {
        lv++;
        s2 = s2->prev;
        if (!s2) break;
      }
      genop_2S(s, OP_ARGARY, cursp(), (lv & 0xf));
      push(); push();         /* ARGARY pushes two values */
      pop(); pop();
      if (tree) {
        node *args = tree->car;
        if (args) {
          n = gen_values(s, args, VAL, 0);
          if (n < 0) {
            n = noop = sendv = 1;
            push();
          }
        }
      }
      if (tree && tree->cdr) {
        codegen(s, tree->cdr, VAL);
        pop();
      }
      else {
        genop_1(s, OP_LOADNIL, cursp());
        push(); pop();
      }
      pop_n(n+1);
      if (sendv) n = CALL_MAXARGS;
      genop_2(s, OP_SUPER, cursp(), n);
      if (val) push();
    }
    break;

  case NODE_ZSUPER:
    {
      codegen_scope *s2 = s;
      int lv = 0, ainfo = 0;

      push();        /* room for receiver */
      while (!s2->mscope) {
        lv++;
        s2 = s2->prev;
        if (!s2) break;
      }
      if (s2) ainfo = s2->ainfo;
      genop_2S(s, OP_ARGARY, cursp(), (ainfo<<4)|(lv & 0xf));
      push(); push(); pop();    /* ARGARY pushes two values */
      if (tree && tree->cdr) {
        codegen(s, tree->cdr, VAL);
        pop();
      }
      pop(); pop();
      genop_2(s, OP_SUPER, cursp(), CALL_MAXARGS);
      if (val) push();
    }
    break;

  case NODE_RETURN:
    if (tree) {
      gen_retval(s, tree);
    }
    else {
      genop_1(s, OP_LOADNIL, cursp());
    }
    if (s->loop) {
      gen_return(s, OP_RETURN_BLK, cursp());
    }
    else {
      gen_return(s, OP_RETURN, cursp());
    }
    if (val) push();
    break;

  case NODE_YIELD:
    {
      codegen_scope *s2 = s;
      int lv = 0, ainfo = 0;
      int n = 0, sendv = 0;

      while (!s2->mscope) {
        lv++;
        s2 = s2->prev;
        if (!s2) break;
      }
      if (s2) ainfo = s2->ainfo;
      push();
      if (tree) {
        n = gen_values(s, tree, VAL, 0);
        if (n < 0) {
          n = sendv = 1;
          push();
        }
      }
      push();pop(); /* space for a block */
      pop_n(n+1);
      genop_2S(s, OP_BLKPUSH, cursp(), (ainfo<<4)|(lv & 0xf));
      if (sendv) n = CALL_MAXARGS;
      genop_3(s, OP_SEND, cursp(), new_sym(s, mrb_intern_lit(s->mrb, "call")), n);
      if (val) push();
    }
    break;

  case NODE_BREAK:
    loop_break(s, tree);
    if (val) push();
    break;

  case NODE_NEXT:
    if (!s->loop) {
      raise_error(s, "unexpected next");
    }
    else if (s->loop->type == LOOP_NORMAL) {
      if (s->ensure_level > s->loop->ensure_level) {
        genop_1(s, OP_EPOP, s->ensure_level - s->loop->ensure_level);
      }
      codegen(s, tree, NOVAL);
      genjmp(s, OP_JMP, s->loop->pc0);
    }
    else {
      if (tree) {
        codegen(s, tree, VAL);
        pop();
      }
      else {
        genop_1(s, OP_LOADNIL, cursp());
      }
      gen_return(s, OP_RETURN, cursp());
    }
    if (val) push();
    break;

  case NODE_REDO:
    if (!s->loop || s->loop->type == LOOP_BEGIN || s->loop->type == LOOP_RESCUE) {
      raise_error(s, "unexpected redo");
    }
    else {
      if (s->ensure_level > s->loop->ensure_level) {
        genop_1(s, OP_EPOP, s->ensure_level - s->loop->ensure_level);
      }
      genjmp(s, OP_JMP, s->loop->pc2);
    }
    if (val) push();
    break;

  case NODE_RETRY:
    {
      const char *msg = "unexpected retry";

      if (!s->loop) {
        raise_error(s, msg);
      }
      else {
        struct loopinfo *lp = s->loop;
        int n = 0;

        while (lp && lp->type != LOOP_RESCUE) {
          if (lp->type == LOOP_BEGIN) {
            n++;
          }
          lp = lp->prev;
        }
        if (!lp) {
          raise_error(s, msg);
        }
        else {
          if (n > 0) {
            genop_1(s, OP_POPERR, n);
          }
          if (s->ensure_level > lp->ensure_level) {
            genop_1(s, OP_EPOP, s->ensure_level - lp->ensure_level);
          }
          genjmp(s, OP_JMP, lp->pc0);
        }
      }
      if (val) push();
    }
    break;

  case NODE_LVAR:
    if (val) {
      int idx = lv_idx(s, nsym(tree));

      if (idx > 0) {
        gen_move(s, cursp(), idx, val);
        if (val && on_eval(s)) genop_0(s, OP_NOP);
      }
      else {
        int lv = 0;
        codegen_scope *up = s->prev;

        while (up) {
          idx = lv_idx(up, nsym(tree));
          if (idx > 0) {
            genop_3(s, OP_GETUPVAR, cursp(), idx, lv);
            break;
          }
          lv++;
          up = up->prev;
        }
      }
      push();
    }
    break;

  case NODE_GVAR:
    {
      int sym = new_sym(s, nsym(tree));

      genop_2(s, OP_GETGV, cursp(), sym);
      if (val) push();
    }
    break;

  case NODE_IVAR:
    {
      int sym = new_sym(s, nsym(tree));

      genop_2(s, OP_GETIV, cursp(), sym);
      if (val) push();
    }
    break;

  case NODE_CVAR:
    {
      int sym = new_sym(s, nsym(tree));

      genop_2(s, OP_GETCV, cursp(), sym);
      if (val) push();
    }
    break;

  case NODE_CONST:
    {
      int sym = new_sym(s, nsym(tree));

      genop_2(s, OP_GETCONST, cursp(), sym);
      if (val) push();
    }
    break;

  case NODE_DEFINED:
    codegen(s, tree, val);
    break;

  case NODE_BACK_REF:
    if (val) {
      char buf[] = {'$', nchar(tree)};
      int sym = new_sym(s, mrb_intern(s->mrb, buf, sizeof(buf)));

      genop_2(s, OP_GETGV, cursp(), sym);
      push();
    }
    break;

  case NODE_NTH_REF:
    if (val) {
      mrb_state *mrb = s->mrb;
      mrb_value str;
      int sym;

      str = mrb_format(mrb, "$%S", mrb_fixnum_value(nint(tree)));
      sym = new_sym(s, mrb_intern_str(mrb, str));
      genop_2(s, OP_GETGV, cursp(), sym);
      push();
    }
    break;

  case NODE_ARG:
    /* should not happen */
    break;

  case NODE_BLOCK_ARG:
    codegen(s, tree, val);
    break;

  case NODE_INT:
    if (val) {
      char *p = (char*)tree->car;
      int base = nint(tree->cdr->car);
      mrb_int i;
      mrb_bool overflow;

      i = readint_mrb_int(s, p, base, FALSE, &overflow);
#ifndef MRB_WITHOUT_FLOAT
      if (overflow) {
        double f = readint_float(s, p, base);
        int off = new_lit(s, mrb_float_value(s->mrb, f));

        genop_2(s, OP_LOADL, cursp(), off);
      }
      else
#endif
      {
        if (i == -1) genop_1(s, OP_LOADI__1, cursp());
        else if (i < 0) genop_2(s, OP_LOADINEG, cursp(), (uint16_t)-i);
        else if (i < 8) genop_1(s, OP_LOADI_0 + (uint8_t)i, cursp());
        else if (i <= 0xffff) genop_2(s, OP_LOADI, cursp(), (uint16_t)i);
        else {
          int off = new_lit(s, mrb_fixnum_value(i));
          genop_2(s, OP_LOADL, cursp(), off);
        }
      }
      push();
    }
    break;

#ifndef MRB_WITHOUT_FLOAT
  case NODE_FLOAT:
    if (val) {
      char *p = (char*)tree;
      mrb_float f = mrb_float_read(p, NULL);
      int off = new_lit(s, mrb_float_value(s->mrb, f));

      genop_2(s, OP_LOADL, cursp(), off);
      push();
    }
    break;
#endif

  case NODE_NEGATE:
    {
      nt = nint(tree->car);
      switch (nt) {
#ifndef MRB_WITHOUT_FLOAT
      case NODE_FLOAT:
        if (val) {
          char *p = (char*)tree->cdr;
          mrb_float f = mrb_float_read(p, NULL);
          int off = new_lit(s, mrb_float_value(s->mrb, -f));

          genop_2(s, OP_LOADL, cursp(), off);
          push();
        }
        break;
#endif

      case NODE_INT:
        if (val) {
          char *p = (char*)tree->cdr->car;
          int base = nint(tree->cdr->cdr->car);
          mrb_int i;
          mrb_bool overflow;

          i = readint_mrb_int(s, p, base, TRUE, &overflow);
#ifndef MRB_WITHOUT_FLOAT
          if (overflow) {
            double f = readint_float(s, p, base);
            int off = new_lit(s, mrb_float_value(s->mrb, -f));

            genop_2(s, OP_LOADL, cursp(), off);
          }
          else {
#endif
            if (i == -1) genop_1(s, OP_LOADI__1, cursp());
            else if (i >= -0xffff) {
              genop_2(s, OP_LOADINEG, cursp(), (uint16_t)-i);
            }
            else {
              int off = new_lit(s, mrb_fixnum_value(i));
              genop_2(s, OP_LOADL, cursp(), off);
            }
#ifndef MRB_WITHOUT_FLOAT
          }
#endif
          push();
        }
        break;

      default:
        if (val) {
          int sym = new_sym(s, mrb_intern_lit(s->mrb, "-@"));
          codegen(s, tree, VAL);
          pop();
          genop_3(s, OP_SEND, cursp(), sym, 0);
          push();
        }
        else {
          codegen(s, tree, NOVAL);
        }
        break;
      }
    }
    break;

  case NODE_STR:
    if (val) {
      char *p = (char*)tree->car;
      size_t len = (intptr_t)tree->cdr;
      int ai = mrb_gc_arena_save(s->mrb);
      int off = new_lit(s, mrb_str_new(s->mrb, p, len));

      mrb_gc_arena_restore(s->mrb, ai);
      genop_2(s, OP_STRING, cursp(), off);
      push();
    }
    break;

  case NODE_HEREDOC:
    tree = ((struct mrb_parser_heredoc_info *)tree)->doc;
    /* fall through */
  case NODE_DSTR:
    if (val) {
      node *n = tree;

      if (!n) {
        genop_1(s, OP_LOADNIL, cursp());
        push();
        break;
      }
      codegen(s, n->car, VAL);
      n = n->cdr;
      while (n) {
        codegen(s, n->car, VAL);
        pop(); pop();
        genop_1(s, OP_STRCAT, cursp());
        push();
        n = n->cdr;
      }
    }
    else {
      node *n = tree;

      while (n) {
        if (nint(n->car->car) != NODE_STR) {
          codegen(s, n->car, NOVAL);
        }
        n = n->cdr;
      }
    }
    break;

  case NODE_WORDS:
    gen_literal_array(s, tree, FALSE, val);
    break;

  case NODE_SYMBOLS:
    gen_literal_array(s, tree, TRUE, val);
    break;

  case NODE_DXSTR:
    {
      node *n;
      int ai = mrb_gc_arena_save(s->mrb);
      int sym = new_sym(s, mrb_intern_lit(s->mrb, "Kernel"));

      genop_1(s, OP_LOADSELF, cursp());
      push();
      codegen(s, tree->car, VAL);
      n = tree->cdr;
      while (n) {
        if (nint(n->car->car) == NODE_XSTR) {
          n->car->car = (struct mrb_ast_node*)(intptr_t)NODE_STR;
          mrb_assert(!n->cdr); /* must be the end */
        }
        codegen(s, n->car, VAL);
        pop(); pop();
        genop_1(s, OP_STRCAT, cursp());
        push();
        n = n->cdr;
      }
      push();                   /* for block */
      pop_n(3);
      sym = new_sym(s, mrb_intern_lit(s->mrb, "`"));
      genop_3(s, OP_SEND, cursp(), sym, 1);
      if (val) push();
      mrb_gc_arena_restore(s->mrb, ai);
    }
    break;

  case NODE_XSTR:
    {
      char *p = (char*)tree->car;
      size_t len = (intptr_t)tree->cdr;
      int ai = mrb_gc_arena_save(s->mrb);
      int off = new_lit(s, mrb_str_new(s->mrb, p, len));
      int sym;

      genop_1(s, OP_LOADSELF, cursp());
      push();
      genop_2(s, OP_STRING, cursp(), off);
      push(); push();
      pop_n(3);
      sym = new_sym(s, mrb_intern_lit(s->mrb, "`"));
      genop_3(s, OP_SEND, cursp(), sym, 1);
      if (val) push();
      mrb_gc_arena_restore(s->mrb, ai);
    }
    break;

  case NODE_REGX:
    if (val) {
      char *p1 = (char*)tree->car;
      char *p2 = (char*)tree->cdr->car;
      char *p3 = (char*)tree->cdr->cdr;
      int ai = mrb_gc_arena_save(s->mrb);
      int sym = new_sym(s, mrb_intern_lit(s->mrb, REGEXP_CLASS));
      int off = new_lit(s, mrb_str_new_cstr(s->mrb, p1));
      int argc = 1;

      genop_1(s, OP_OCLASS, cursp());
      genop_2(s, OP_GETMCNST, cursp(), sym);
      push();
      genop_2(s, OP_STRING, cursp(), off);
      push();
      if (p2 || p3) {
        if (p2) { /* opt */
          off = new_lit(s, mrb_str_new_cstr(s->mrb, p2));
          genop_2(s, OP_STRING, cursp(), off);
        }
        else {
          genop_1(s, OP_LOADNIL, cursp());
        }
        push();
        argc++;
        if (p3) { /* enc */
          off = new_lit(s, mrb_str_new(s->mrb, p3, 1));
          genop_2(s, OP_STRING, cursp(), off);
          push();
          argc++;
        }
      }
      push(); /* space for a block */
      pop_n(argc+2);
      sym = new_sym(s, mrb_intern_lit(s->mrb, "compile"));
      genop_3(s, OP_SEND, cursp(), sym, argc);
      mrb_gc_arena_restore(s->mrb, ai);
      push();
    }
    break;

  case NODE_DREGX:
    if (val) {
      node *n = tree->car;
      int ai = mrb_gc_arena_save(s->mrb);
      int sym = new_sym(s, mrb_intern_lit(s->mrb, REGEXP_CLASS));
      int argc = 1;
      int off;
      char *p;

      genop_1(s, OP_OCLASS, cursp());
      genop_2(s, OP_GETMCNST, cursp(), sym);
      push();
      codegen(s, n->car, VAL);
      n = n->cdr;
      while (n) {
        codegen(s, n->car, VAL);
        pop(); pop();
        genop_1(s, OP_STRCAT, cursp());
        push();
        n = n->cdr;
      }
      n = tree->cdr->cdr;
      if (n->car) { /* tail */
        p = (char*)n->car;
        off = new_lit(s, mrb_str_new_cstr(s->mrb, p));
        codegen(s, tree->car, VAL);
        genop_2(s, OP_STRING, cursp(), off);
        pop();
        genop_1(s, OP_STRCAT, cursp());
        push();
      }
      if (n->cdr->car) { /* opt */
        char *p2 = (char*)n->cdr->car;
        off = new_lit(s, mrb_str_new_cstr(s->mrb, p2));
        genop_2(s, OP_STRING, cursp(), off);
        push();
        argc++;
      }
      if (n->cdr->cdr) { /* enc */
        char *p2 = (char*)n->cdr->cdr;
        off = new_lit(s, mrb_str_new_cstr(s->mrb, p2));
        genop_2(s, OP_STRING, cursp(), off);
        push();
        argc++;
      }
      push(); /* space for a block */
      pop_n(argc+2);
      sym = new_sym(s, mrb_intern_lit(s->mrb, "compile"));
      genop_3(s, OP_SEND, cursp(), sym, argc);
      mrb_gc_arena_restore(s->mrb, ai);
      push();
    }
    else {
      node *n = tree->car;

      while (n) {
        if (nint(n->car->car) != NODE_STR) {
          codegen(s, n->car, NOVAL);
        }
        n = n->cdr;
      }
    }
    break;

  case NODE_SYM:
    if (val) {
      int sym = new_sym(s, nsym(tree));

      genop_2(s, OP_LOADSYM, cursp(), sym);
      push();
    }
    break;

  case NODE_DSYM:
    codegen(s, tree, val);
    if (val) {
      gen_intern(s);
    }
    break;

  case NODE_SELF:
    if (val) {
      genop_1(s, OP_LOADSELF, cursp());
      push();
    }
    break;

  case NODE_NIL:
    if (val) {
      genop_1(s, OP_LOADNIL, cursp());
      push();
    }
    break;

  case NODE_TRUE:
    if (val) {
      genop_1(s, OP_LOADT, cursp());
      push();
    }
    break;

  case NODE_FALSE:
    if (val) {
      genop_1(s, OP_LOADF, cursp());
      push();
    }
    break;

  case NODE_ALIAS:
    {
      int a = new_sym(s, nsym(tree->car));
      int b = new_sym(s, nsym(tree->cdr));

      genop_2(s, OP_ALIAS, a, b);
      if (val) {
        genop_1(s, OP_LOADNIL, cursp());
        push();
      }
    }
   break;

  case NODE_UNDEF:
    {
      node *t = tree;

      while (t) {
        int symbol = new_sym(s, nsym(t->car));
        genop_1(s, OP_UNDEF, symbol);
        t = t->cdr;
      }
      if (val) {
        genop_1(s, OP_LOADNIL, cursp());
        push();
      }
    }
    break;

  case NODE_CLASS:
    {
      int idx;
      node *body;

      if (tree->car->car == (node*)0) {
        genop_1(s, OP_LOADNIL, cursp());
        push();
      }
      else if (tree->car->car == (node*)1) {
        genop_1(s, OP_OCLASS, cursp());
        push();
      }
      else {
        codegen(s, tree->car->car, VAL);
      }
      if (tree->cdr->car) {
        codegen(s, tree->cdr->car, VAL);
      }
      else {
        genop_1(s, OP_LOADNIL, cursp());
        push();
      }
      pop(); pop();
      idx = new_sym(s, nsym(tree->car->cdr));
      genop_2(s, OP_CLASS, cursp(), idx);
      body = tree->cdr->cdr->car;
      if (nint(body->cdr->car) == NODE_BEGIN && body->cdr->cdr == NULL) {
        genop_1(s, OP_LOADNIL, cursp());
      }
      else {
        idx = scope_body(s, body, val);
        genop_2(s, OP_EXEC, cursp(), idx);
      }
      if (val) {
        push();
      }
    }
    break;

  case NODE_MODULE:
    {
      int idx;

      if (tree->car->car == (node*)0) {
        genop_1(s, OP_LOADNIL, cursp());
        push();
      }
      else if (tree->car->car == (node*)1) {
        genop_1(s, OP_OCLASS, cursp());
        push();
      }
      else {
        codegen(s, tree->car->car, VAL);
      }
      pop();
      idx = new_sym(s, nsym(tree->car->cdr));
      genop_2(s, OP_MODULE, cursp(), idx);
      if (nint(tree->cdr->car->cdr->car) == NODE_BEGIN &&
          tree->cdr->car->cdr->cdr == NULL) {
        genop_1(s, OP_LOADNIL, cursp());
      }
      else {
        idx = scope_body(s, tree->cdr->car, val);
        genop_2(s, OP_EXEC, cursp(), idx);
      }
      if (val) {
        push();
      }
    }
    break;

  case NODE_SCLASS:
    {
      int idx;

      codegen(s, tree->car, VAL);
      pop();
      genop_1(s, OP_SCLASS, cursp());
      if (nint(tree->cdr->car->cdr->car) == NODE_BEGIN &&
          tree->cdr->car->cdr->cdr == NULL) {
        genop_1(s, OP_LOADNIL, cursp());
      }
      else {
        idx = scope_body(s, tree->cdr->car, val);
        genop_2(s, OP_EXEC, cursp(), idx);
      }
      if (val) {
        push();
      }
    }
    break;

  case NODE_DEF:
    {
      int sym = new_sym(s, nsym(tree->car));
      int idx = lambda_body(s, tree->cdr, 0);

      genop_1(s, OP_TCLASS, cursp());
      push();
      genop_2(s, OP_METHOD, cursp(), idx);
      push(); pop();
      pop();
      genop_2(s, OP_DEF, cursp(), sym);
      if (val) {
        genop_2(s, OP_LOADSYM, cursp(), sym);
        push();
      }
    }
    break;

  case NODE_SDEF:
    {
      node *recv = tree->car;
      int sym = new_sym(s, nsym(tree->cdr->car));
      int idx = lambda_body(s, tree->cdr->cdr, 0);

      codegen(s, recv, VAL);
      pop();
      genop_1(s, OP_SCLASS, cursp());
      push();
      genop_2(s, OP_METHOD, cursp(), idx);
      pop();
      genop_2(s, OP_DEF, cursp(), sym);
      if (val) {
        genop_2(s, OP_LOADSYM, cursp(), sym);
        push();
      }
    }
    break;

  case NODE_POSTEXE:
    codegen(s, tree, NOVAL);
    break;

  default:
    break;
  }
 exit:
  s->rlev = rlev;
}