#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct opcode_description {int length; int flags; } ;
struct locfile {int dummy; } ;
struct bytecode {int nsubfunctions; int codelen; int* code; int nlocals; void* constants; struct bytecode** subfunctions; void* debuginfo; scalar_t__ nclosures; struct bytecode* parent; TYPE_1__* globals; } ;
typedef  void* jv ;
struct TYPE_17__ {int intval; TYPE_3__* target; void* constant; int /*<<< orphan*/ * cfunc; } ;
struct TYPE_15__ {TYPE_5__* first; } ;
struct TYPE_19__ {TYPE_5__* first; TYPE_5__* last; } ;
struct TYPE_18__ {scalar_t__ op; int bytecode_pos; char* symbol; TYPE_4__ imm; struct TYPE_18__* bound_by; struct TYPE_18__* next; TYPE_2__ arglist; TYPE_6__ subfn; struct bytecode* compiled; } ;
typedef  TYPE_5__ inst ;
typedef  TYPE_6__ block ;
struct TYPE_16__ {int bytecode_pos; } ;
struct TYPE_14__ {int /*<<< orphan*/ * cfunctions; void* cfunc_names; int /*<<< orphan*/  ncfunctions; } ;

/* Variables and functions */
 int ARG_NEWCLOSURE ; 
 TYPE_6__ BLOCK (TYPE_6__,int /*<<< orphan*/ ) ; 
 scalar_t__ CALL_BUILTIN ; 
 scalar_t__ CALL_JQ ; 
 scalar_t__ CLOSURE_CREATE ; 
 scalar_t__ CLOSURE_CREATE_C ; 
 scalar_t__ CLOSURE_PARAM ; 
 scalar_t__ CLOSURE_REF ; 
 int OP_HAS_BRANCH ; 
 int OP_HAS_CONSTANT ; 
 int OP_HAS_VARIABLE ; 
 int /*<<< orphan*/  RET ; 
 int /*<<< orphan*/  UNKNOWN_LOCATION ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_free (TYPE_6__) ; 
 scalar_t__ expand_call_arglist (TYPE_6__*,void*,void**) ; 
 TYPE_6__ gen_noop () ; 
 int /*<<< orphan*/  gen_op_simple (int /*<<< orphan*/ ) ; 
 void* jv_array () ; 
 void* jv_array_append (void*,void*) ; 
 int jv_array_length (void*) ; 
 void* jv_copy (void*) ; 
 struct bytecode* jv_mem_alloc (int) ; 
 void* jv_mem_calloc (int,int) ; 
 void* jv_object () ; 
 void* jv_object_set (void*,void*,void*) ; 
 void* jv_string (char*) ; 
 int /*<<< orphan*/  locfile_locate (struct locfile*,int /*<<< orphan*/ ,char*,int) ; 
 int nesting_level (struct bytecode*,TYPE_5__*) ; 
 struct opcode_description* opcode_describe (scalar_t__) ; 

__attribute__((used)) static int compile(struct bytecode* bc, block b, struct locfile* lf, jv args, jv *env) {
  int errors = 0;
  int pos = 0;
  int var_frame_idx = 0;
  bc->nsubfunctions = 0;
  errors += expand_call_arglist(&b, args, env);
  b = BLOCK(b, gen_op_simple(RET));
  jv localnames = jv_array();
  for (inst* curr = b.first; curr; curr = curr->next) {
    if (!curr->next) assert(curr == b.last);
    int length = opcode_describe(curr->op)->length;
    if (curr->op == CALL_JQ) {
      for (inst* arg = curr->arglist.first; arg; arg = arg->next) {
        length += 2;
      }
    }
    pos += length;
    curr->bytecode_pos = pos;
    curr->compiled = bc;

    assert(curr->op != CLOSURE_REF && curr->op != CLOSURE_PARAM);

    if ((opcode_describe(curr->op)->flags & OP_HAS_VARIABLE) &&
        curr->bound_by == curr) {
      curr->imm.intval = var_frame_idx++;
      localnames = jv_array_append(localnames, jv_string(curr->symbol));
    }

    if (curr->op == CLOSURE_CREATE) {
      assert(curr->bound_by == curr);
      curr->imm.intval = bc->nsubfunctions++;
    }
    if (curr->op == CLOSURE_CREATE_C) {
      assert(curr->bound_by == curr);
      int idx = bc->globals->ncfunctions++;
      bc->globals->cfunc_names = jv_array_append(bc->globals->cfunc_names,
                                                 jv_string(curr->symbol));
      bc->globals->cfunctions[idx] = *curr->imm.cfunc;
      curr->imm.intval = idx;
    }
  }
  if (pos > 0xFFFF) {
    // too long for program counter to fit in uint16_t
    locfile_locate(lf, UNKNOWN_LOCATION,
        "function compiled to %d bytes which is too long", pos);
    errors++;
  }
  bc->codelen = pos;
  bc->debuginfo = jv_object_set(bc->debuginfo, jv_string("locals"), localnames);
  if (bc->nsubfunctions) {
    bc->subfunctions = jv_mem_calloc(sizeof(struct bytecode*), bc->nsubfunctions);
    for (inst* curr = b.first; curr; curr = curr->next) {
      if (curr->op == CLOSURE_CREATE) {
        struct bytecode* subfn = jv_mem_alloc(sizeof(struct bytecode));
        bc->subfunctions[curr->imm.intval] = subfn;
        subfn->globals = bc->globals;
        subfn->parent = bc;
        subfn->nclosures = 0;
        subfn->debuginfo = jv_object_set(jv_object(), jv_string("name"), jv_string(curr->symbol));
        jv params = jv_array();
        for (inst* param = curr->arglist.first; param; param = param->next) {
          assert(param->op == CLOSURE_PARAM);
          assert(param->bound_by == param);
          param->imm.intval = subfn->nclosures++;
          param->compiled = subfn;
          params = jv_array_append(params, jv_string(param->symbol));
        }
        subfn->debuginfo = jv_object_set(subfn->debuginfo, jv_string("params"), params);
        errors += compile(subfn, curr->subfn, lf, args, env);
        curr->subfn = gen_noop();
      }
    }
  } else {
    bc->subfunctions = 0;
  }
  uint16_t* code = jv_mem_calloc(sizeof(uint16_t), bc->codelen);
  bc->code = code;
  pos = 0;
  jv constant_pool = jv_array();
  int maxvar = -1;
  if (!errors) for (inst* curr = b.first; curr; curr = curr->next) {
    const struct opcode_description* op = opcode_describe(curr->op);
    if (op->length == 0)
      continue;
    code[pos++] = curr->op;
    assert(curr->op != CLOSURE_REF && curr->op != CLOSURE_PARAM);
    if (curr->op == CALL_BUILTIN) {
      assert(curr->bound_by->op == CLOSURE_CREATE_C);
      assert(!curr->arglist.first);
      code[pos++] = (uint16_t)curr->imm.intval;
      code[pos++] = curr->bound_by->imm.intval;
    } else if (curr->op == CALL_JQ) {
      assert(curr->bound_by->op == CLOSURE_CREATE ||
             curr->bound_by->op == CLOSURE_PARAM);
      code[pos++] = (uint16_t)curr->imm.intval;
      code[pos++] = nesting_level(bc, curr->bound_by);
      code[pos++] = curr->bound_by->imm.intval |
        (curr->bound_by->op == CLOSURE_CREATE ? ARG_NEWCLOSURE : 0);
      for (inst* arg = curr->arglist.first; arg; arg = arg->next) {
        assert(arg->op == CLOSURE_REF && arg->bound_by->op == CLOSURE_CREATE);
        code[pos++] = nesting_level(bc, arg->bound_by);
        code[pos++] = arg->bound_by->imm.intval | ARG_NEWCLOSURE;
      }
    } else if ((op->flags & OP_HAS_CONSTANT) && (op->flags & OP_HAS_VARIABLE)) {
      // STORE_GLOBAL: constant global, basically
      code[pos++] = jv_array_length(jv_copy(constant_pool));
      constant_pool = jv_array_append(constant_pool, jv_copy(curr->imm.constant));
      code[pos++] = nesting_level(bc, curr->bound_by);
      uint16_t var = (uint16_t)curr->bound_by->imm.intval;
      code[pos++] = var;
    } else if (op->flags & OP_HAS_CONSTANT) {
      code[pos++] = jv_array_length(jv_copy(constant_pool));
      constant_pool = jv_array_append(constant_pool, jv_copy(curr->imm.constant));
    } else if (op->flags & OP_HAS_VARIABLE) {
      code[pos++] = nesting_level(bc, curr->bound_by);
      uint16_t var = (uint16_t)curr->bound_by->imm.intval;
      code[pos++] = var;
      if (var > maxvar) maxvar = var;
    } else if (op->flags & OP_HAS_BRANCH) {
      assert(curr->imm.target->bytecode_pos != -1);
      assert(curr->imm.target->bytecode_pos > pos); // only forward branches
      code[pos] = curr->imm.target->bytecode_pos - (pos + 1);
      pos++;
    } else if (op->length > 1) {
      assert(0 && "codegen not implemented for this operation");
    }
  }
  bc->constants = constant_pool;
  bc->nlocals = maxvar + 2; // FIXME: frames of size zero?
  block_free(b);
  return errors;
}