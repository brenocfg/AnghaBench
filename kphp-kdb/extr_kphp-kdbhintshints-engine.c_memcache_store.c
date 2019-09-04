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
struct connection {int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT ; 
 int MAX_VALUE_LEN ; 
 int /*<<< orphan*/  MESSAGE (struct connection*) ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* buf ; 
 int /*<<< orphan*/  check_object_id (int) ; 
 int /*<<< orphan*/  cmd_global ; 
 int do_add_user_object (int,int,long long) ; 
 int do_nullify_user_rating (int) ; 
 int do_set_object_type (int,long long,int) ; 
 scalar_t__ do_set_user_info (int,int) ; 
 int do_set_user_object_rating (int,int,long long,float,int) ; 
 int do_set_user_object_type (int,int,long long,int) ; 
 scalar_t__ do_set_user_rating_state (int,int) ; 
 int do_user_object_winner (int,int,int,long long,int,int*) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  history_q_add (char*,int /*<<< orphan*/ ) ; 
 char* msg_get_buf (int /*<<< orphan*/ ) ; 
 scalar_t__ msg_reinit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  safe_read_in (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  set ; 
 int sscanf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_only ; 

int memcache_store (struct connection *c, int op, const char *old_key, int old_key_len, int flags, int delay, int size) {
  INIT;

  if (verbosity > 1) {
    fprintf (stderr, "memcache_store: key='%s', key_len=%d, value_len=%d, ", old_key, old_key_len, size);
  }

  char *key;
  int key_len;

  eat_at (old_key, old_key_len, &key, &key_len);

  history_q_add (key, 0);

  if (size + 1 < MAX_VALUE_LEN) {
    if (!write_only && key_len >= 12 && (!strncmp (key, "sort_by_rate", 12) || !strncmp (key, "sort_by_rand", 12))) {
      int random_tag;

      if (sscanf (key + 12, "%*d_%d", &random_tag) != 1) {
        RETURN(set, -2);
      }

      if (msg_reinit (MESSAGE (c), size, random_tag) < 0) {
        RETURN(set, -2);
      }
      safe_read_in (&c->In, msg_get_buf (MESSAGE (c)), size);

      RETURN(set, 1);
    }

    safe_read_in (&c->In, buf, size);
    buf[size] = 0;

    //Обнуление рейтинга пользователя
    //set ("user_rating_nullify{$user_id}", "")
    if (key_len >= 19 && !strncmp (key, "user_rating_nullify", 19)) {
      int user_id;
      int result = sscanf (key + 19, "%d", &user_id) == 1;

      if (verbosity > 1) {
        fprintf (stderr, "user rating nullify %d\n", user_id);
      }

      result &= do_nullify_user_rating (user_id);

      RETURN(set, result);
    }

    //Изменение состояния пользователя
    //set ("user_rating_state{$user_id}", "{$flag}")
    if (key_len >= 17 && !strncmp (key, "user_rating_state", 17)) {
      int user_id, type;

      if (verbosity > 1) {
        fprintf (stderr, "user rating state\n");
      }

      int result = (sscanf (key + 17, "%d", &user_id) == 1 && sscanf (buf, "%d", &type) == 1 && do_set_user_rating_state (user_id, type));

      RETURN(set, result);
    }

    //Получение статуса пользователя
    //set ("user_info{$user_id}", "{$text}")
    if (key_len >= 9 && !strncmp (key, "user_info", 9)) {
      int user_id, info;

      if (verbosity > 1) {
        fprintf (stderr, "set user info\n");
      }

      int result = sscanf (key + 9, "%d", &user_id) == 1 && sscanf (buf, "%d", &info) == 1 && do_set_user_info (user_id, info);

      RETURN(set, result);
    }

    //Увеличение рейтинга одного из объектов пользователя за счёт уменьшения рейтинга других
    //set ("user_object_winner{$user_id},{$type}:{$winner_id}*{$rating_num}", "{$loser_n},{$loser_id},...,{$loser_id}")
    if (key_len >= 18 && !strncmp (key, "user_object_winner", 18)) {
      int user_id, type;
      long long object_id;
      int object_id2;
      int add = -1, add2 = -1;

      int t = sscanf (key + 18, "%d,%d:%lld%n_%d%n", &user_id, &type, &object_id, &add, &object_id2, &add2);
      if (t == 3 || t == 4) {
        if (t == 4) {
          if (object_id != user_id && object_id2 != user_id) {
            RETURN(set, 0);
          }
          if (object_id == user_id) {
            object_id = object_id2;
          }
          add = add2;
        }

        assert (add != -1);
        int num;
        if (sscanf (key + 18 + add, "*%d", &num) != 1) {
          num = 0;
        }

        int losers_cnt;
        if (sscanf (buf, "%d%n", &losers_cnt, &add) == 1 && 0 < losers_cnt && losers_cnt <= 16000) {
          static int losers[16000];
          int cur_add = 0, i;
          for (i = 0; i < losers_cnt; i++) {
            if (buf[add] != ',') {
              RETURN(set, 0);
            }
            add++;

            if (sscanf (buf + add, "%d%n", &losers[i], &cur_add) != 1 || !check_object_id (losers[i]) || losers[i] == object_id) {
              RETURN(set, 0);
            }
            add += cur_add;
          }
          if (buf[add]) {
            RETURN(set, 0);
          }

          int result = do_user_object_winner (user_id, type, num, object_id, losers_cnt, losers);

          RETURN(set, result);
        }
      }

      RETURN(set, 0);
    }

    //Изменение типа объекта для одного пользователя
    //set ("user_object_type{$user_id},{$type}:{$object_id}", "{$new_type}")
    if (key_len >= 16 && !strncmp (key, "user_object_type", 16)) {
      int user_id, type;
      long long object_id;
      int object_id2;

      int t = sscanf (key + 16, "%d,%d:%lld_%d", &user_id, &type, &object_id, &object_id2);
      if (t == 3 || t == 4) {
        if (t == 4) {
          if (object_id != user_id && object_id2 != user_id) {
            RETURN(set, 0);
          }
          if (object_id == user_id) {
            object_id = object_id2;
          }
        }

        int new_type;
        if (sscanf (buf, "%d", &new_type) == 1) {
          RETURN(set, do_set_user_object_type (user_id, type, object_id, new_type));
        }
      }

      RETURN(set, 0);
    }

    //Изменение рейтинга объекта для одного пользователя
    //set ("user_object_rating{$user_id},{$type}:{$object_id}", "{$new_rating}")
    if (key_len >= 18 && !strncmp (key, "user_object_rating", 18)) {
      int user_id, type;
      long long object_id;
      int object_id2;
      int add = -1;

      int t = sscanf (key + 18, "%d,%d:%lld%n_%d%n", &user_id, &type, &object_id, &add, &object_id2, &add);
      if (t == 3 || t == 4) {
        if (t == 4) {
          if (object_id != user_id && object_id2 != user_id) {
            RETURN(set, 0);
          }
          if (object_id == user_id) {
            object_id = object_id2;
          }
        }
        int num;
        if (sscanf (key + 18 + add, "*%d", &num) != 1) {
          num = 0;
        }

        float new_rating;
        int pos;
        if (sscanf (buf, "%f%n", &new_rating, &pos) != 1 || buf[pos]) {
          RETURN(set, 0);
        }

        int result = do_set_user_object_rating (user_id, type, object_id, new_rating, num);
        RETURN(set, result);
      }

      RETURN(set, 0);
    }

    //Добавление нового объекта для одного пользователя
    //set ("user_object{$user_id},{$type}:{$object_id}", "{$text}")
    if (key_len >= 11 && !strncmp (key, "user_object", 11)) {
      int user_id, type;
      long long object_id;
      int object_id2;

      int t = sscanf (key + 11, "%d,%d:%lld_%d", &user_id, &type, &object_id, &object_id2);
      if (t == 3 || t == 4) {
        if (t == 4) {
          if (object_id != user_id && object_id2 != user_id) {
            RETURN(set, 0);
          }
          if (object_id == user_id) {
            object_id = object_id2;
          }
        }
#ifdef HINTS
        RETURN(set, do_add_user_object (user_id, type, object_id, size, buf));
#else
        RETURN(set, do_add_user_object (user_id, type, object_id));
#endif
      }

      RETURN(set, 0);
    }

#ifdef HINTS
    //Изменение ключевых слов для данного глобального объекта
    //set ("object_text{$type}:{$object_id}", "{$text}")
    if (key_len >= 11 && !strncmp (key, "object_text", 11)) {
      int type;
      long long object_id;

      if (sscanf (key + 11, "%d:%lld", &type, &object_id) == 2) {
        cmd_global++;
        RETURN(set, do_add_object_text (type, object_id, size, buf));
      }

      RETURN(set, 0);
    }
#endif

    //Изменение типа глобального объекта
    //set ("object_type{$type}:{$object_id}", "{$new_type}")
    if (key_len >= 11 && !strncmp (key, "object_type", 11)) {
      int type;
      long long object_id;
      int new_type;

      if (sscanf (key + 11, "%d:%lld", &type, &object_id) == 2 && 
          sscanf (buf, "%d", &new_type) == 1) {
        cmd_global++;
        RETURN(set, do_set_object_type (type, object_id, new_type));
      }

      RETURN(set, 0);
    }

    RETURN(set, 0);
  }

  RETURN(set, -2);
}